#include "Common.hlsli" // 쉐이더에서도 include 사용 가능

#define PI 3.141592

Texture3D<float> densityTex : register(t5); // t5 부터 시작
Texture3D<float> lightingTex : register(t6);
Texture3D<float> temperatureTex : register(t7);

cbuffer Consts : register(b3) // b3 주의
{
    float3 uvwOffset; // 미사용
    float lightAbsorptionCoeff = 5.0;
    float3 lightDir = float3(0, 1, 0);
    float densityAbsorption = 10.0;
    float3 lightColor = float3(1, 1, 1) * 40.0;
    float aniso = 0.3;
}

// 박스 가장자리 좌표로부터 3D 텍스춰 좌표 계산
float3 GetUVW(float3 posModel)
{
    return (posModel.xyz + 1.0) * 0.5;
}

// https://wallisc.github.io/rendering/2020/05/02/Volumetric-Rendering-Part-2.html
float BeerLambert(float absorptionCoefficient, float distanceTraveled)
{
    return exp(-absorptionCoefficient * distanceTraveled);
}

// Henyey-Greenstein phase function
// Graph: https://www.researchgate.net/figure/Henyey-Greenstein-phase-function-as-a-function-of-O-O-for-isotropic-scattering-g_fig1_338086693
float HenyeyGreensteinPhase(in float3 L, in float3 V, in float aniso)
{
    // 빛의 방향과 시점의 방향 사이의 각도에 따라서 빛을 얼마나 볼수 있는지가 정해짐
    
    // V: eye - pos 
    // L: 조명을 향하는 방향
    // https://www.shadertoy.com/view/7s3SRH
    
    float cosT = dot(L, -V); // -V : eye -> pos
    float g = aniso;
    return (1.0 - g * g) / (4.0 * PI * pow(abs(1.0 + g * g - 2.0 * g * cosT), 3.0 / 2.0));
}

// https://github.com/maruel/temperature/blob/master/temperature.go
float3 ToRGB(float kelvin)
{
    if (kelvin == 6500.0f)
    {
        return float3(1.0f, 1.0f, 1.0f);
    }

    float temperature = kelvin * 0.01f;
    if (kelvin < 6500.0f)
    {
        float b = 0.0;
        float r = 1.0;
        float green = temperature - 2.0;
        float g = (-155.25485562709179f - 0.44596950469579133f * green + 104.49216199393888f * log(green));

        if (kelvin > 2000.0f)
        {
            float blue = temperature - 10.0f;
            b = (-254.76935184120902f + 0.8274096064007395f * blue + 115.67994401066147f * log(blue)) * 255.0f;
        }
        return float3(r, g, b);
    }

    float b = 1.0f;
    float red = temperature - 55.0f;
    float r = (351.97690566805693f + 0.114206453784165f * red - 40.25366309332127f * log(red));
    float green = temperature - 50.0f;
    float g = (325.4494125711974f + 0.07943456536662342f * green - 28.0852963507957f * log(green)) * 255.0f;
    return float3(r, g, b);
}

float SDF_Sphere(float3 posModel, float3 center, float radius)
{
    return length(posModel - center) - radius;
}

float4 main(PixelShaderInput input) : SV_TARGET
{
    // 물체 입장에서 눈의 위치가 어디인지 역으로 계산
    // 물체 좌표계에서 light나 eye방향으로 레이를 통해 추적하기 때문
    // 반대로 해도 괜찮으나, 해당 방식이 연산이나 사고하기 용이해서 사용하는 것
    float3 eyeModel = mul(float4(eyeWorld, 1), worldInv).xyz; // 월드->모델 역변환
    float3 dirModel = normalize(input.posModel - eyeModel);
    
    int numSteps = 128;
    float stepSize = 2.0 / float(numSteps); // 박스 길이가 2.0
    
    // 일반적으로 값을 하드코딩해서 먼저 구현한 후 CB로 받아서 구현하는 식으로 확장함
    // float absorptionCoeff = 10.0;
    float3 volumeAlbedo = float3(1, 1, 1); // 볼륨색
    // float3 lightColor = float3(1, 1, 1) * 40.0;
    
    // 0에서 더해가면서 1이 되었을 때 끝내도 되나, 해당 방식이 사고과정에 용이해서 소진하는 방식으로 사용
    float4 color = float4(0, 0, 0, 1); // visibility 1.0으로 시작
    float3 posModel = input.posModel + dirModel * 1e-6; // 살짝 들어간 상태에서 시작

    // 주의: color.a에 "투명도"로 사용하다가 마지막에 "불투명도"로 바꿔줌
    
    [loop] // [unroll] 사용 시 쉐이더 생성이 너무 느림 [unroll은 컴파일시 다 풀어버리기 때문에 생성 때 시간이 오래걸리는 대신 실행 시 빨라짐]
    for (int i = 0; i < numSteps; i++)
    {
        // Model -> Texture 좌표계
        float3 uvw = GetUVW(posModel); // +uvwOffset; 미사용 
        
        // 물체 렌더링
        // 볼륨과 오브젝트를 같이 렌더링 할 수 있음
        // 현재는 오브젝트가 하드코딩 되어있으나, 추후 개인프로젝트에선 분리
        {
          float3 objCenter = float3(0.15, 0.3, 0.5);
          float objRadius = 0.06;
          float dist = length((uvw - objCenter) * float3(2, 1, 1)) / objRadius;
    
          if (dist < 1.0)
          {
              color.rgb += float3(0, 0, 1) * color.a; // Blue ball
              color.a = 0;
          
              // 참고: 물체들을 레스터화로 먼저 렌더링 하고 깊이를 참고해서 블렌딩할 수도 있습니다.
          
              break;
          }
        }
        
        // 이미 계산된 것을 사용
        float density = densityTex.SampleLevel(linearClampSampler, uvw, 0).r;
        
        // float3 center = (0.5, 0.5, 0.5);
        // float len = length(uvw - center);
        // float c = abs(len) < 0.5 ? 1.0 : 0.0;
        // density *= c;
        
        // Signed Distance Function
        //  - 각 지점(x)이 어떤 표면으로부터 얼마나 떨어져있는지,
        //    그리고 해당 지점이 표면의 어디(내부/외부/표면 등)에 위치하는지를 판단해주는 함수
        
        // SDF
        // - 음수라면 내부 혹은 표면, 양수라면 외부 
        // - 각 형태을 나타내는 함수식을 기반으로 여러 형태의 범위를 합칠 수 있음
        //      - f1과 f2의 도형이 합쳐진 범위 내에서 판별하고 싶다할 경우 min(f1, f2)를 기반으로 계산하면 됨
        //        min을 기반으로 계산할 경우 여러 형태의 함수식 중 가장 가까운(적합한) 함수식으로 설명 및 연산할 수 있게 됨      
        //
        // 표면을 정의하는 방법
        //  - Explicit Surface (명시적 표면)
        //      - 정의방식   : 점(Vertex)과 면(Primitive)으로 표면을 직접적으로 정의
        //      - 판별기준   : 메시의 기하학적 구조
        //      - 데이터형태 : 이산적(Discrete)
        //      - 장점
        //          1. 렌더링·모델링 용이
        //          2. 하드웨어 최적화
        //      - 예시
        //          1. 폴리곤 기반 3D 모델링
        //          2. 파라메트릭 메쉬
        //          3. NURBS
        //
        //  - Implicit Surface (암시적 표면)
        //      - 정의방식   : 함수식(Functions)으로 간접 정의
        //      - 판별기준   : 함수값의 부호
        //      - 데이터형태 : 연속적(Continuous)
        //      - 장점
        //          1. 충돌, 부피, 블렌딩 표현 용이
        //          2. 도형의 합,차를 구현하기 용이
        //      - 예시
        //          1. Signed Distance Field (SDF)
        //              - 함수로 운용하거나, 복잡한 경우 텍스쳐에 저장하여 사용할 수도 있음
        //          2. Level Set Method
        //      
        
        // [1603 예제에서만 사용]
        // float f1 = SDF_Sphere(posModel, float3(-0.15, 0.0, 0.0), 0.3);
        // float f2 = SDF_Sphere(posModel, float3(+0.15, 0.0, 0.0), 0.3);
        // float sdf = min(f1, f2);
        // 
        // if (sdf <= 0.0)
        // {
        //     // do Nothing
        // }
        // else
        // {
        //     density *= saturate(1.0 - sdf * 10.0);
        // }
        
        // float lighting = lightingTex.SampleLevel(linearClampSampler, uvw, 0).r;
        float lighting = 1.0; // 라이트맵이 없는 예제

        if (density.r > 1e-3)
        {
            float prevAlpha = color.a;
            color.a *= BeerLambert(densityAbsorption * density.r, stepSize); // BeerLambert 비율
            float absorptionFromMarch = prevAlpha - color.a;
            
            // density의 감쇄는 비율로 일어남
            // 따라서 이전 값과 비율에 의해서 줄어든 값의 정량적 차이가 absorptionFromMarch 인 것
            
           
            color.rgb += absorptionFromMarch * volumeAlbedo * lightColor
                         * density * lighting // 따라서 해당 값 만큼의 조명(컬러)가 추가됨
                         * HenyeyGreensteinPhase(lightDir, dirModel, aniso);
            // lightDir : 조명이 오는 방향
            // dirModel : 물체를 바라보는 방향
            // L, V 모두 -를 곱해줘서 결과적으로 구현이 동일해짐
        }
        
        posModel += dirModel * stepSize;
        
        if (abs(posModel.x) > 1 || abs(posModel.y) > 1 || abs(posModel.z) > 1)
            break;
        
        if (color.a < 1e-3)
            break;

    }

    color = saturate(color);
    color.a = 1.0 - color.a; // a는 불투명도 (Visiblity가 낮을수록 진하게 표현되야 하기 때문에 뒤집음) [0, 1] -> [1, 0]
                             // (1.0 - color.a)은 추후 별도로 변수(ex. Visibility)를 구성해도 좋음
    
    return color;
}

// 실행속도를 높이는게 정말 중요하다면 레이트레이싱 대신 텍스쳐나 단면을 겹치는 방식을 사용하는게 훨씬 나음