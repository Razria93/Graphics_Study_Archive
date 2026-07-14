cbuffer BillboardPointsConstantData : register(b0)
{
    float3 eyeWorld;
    float width;
    Matrix model; // For vertex shader
    Matrix view; // For vertex shader
    Matrix proj; // For vertex shader
    float time;
    float3 padding;
};

Texture2DArray g_texArray : register(t0);
SamplerState g_sampler : register(s0);

struct PixelShaderInput
{
    float4 pos : SV_POSITION; // Screen position
    float4 posWorld : POSITION0;
    float4 center : POSITION1;
    float2 texCoord : TEXCOORD;
    uint primID : SV_PrimitiveID;
};

struct PixelShaderOutput
{
    float4 pixelColor : SV_Target0;
};

// ShaderToy Fireball 2
// https://www.shadertoy.com/view/wdVXWR

float3 fire_color(float x)
{
    return
        // red
        float3(1., 0., 0.) * x
        // yellow
        + float3(1., 1., 0.) * clamp(x - .5, 0., 1.)
        // white
        + float3(1., 1., 1.) * clamp(x - .7, 0., 1.);
}

Matrix rotate(float a, float3 v)
{
    float c = cos(a);
    float3 ci = (1. - c) * v;
    float3 s = sin(a) * v;

    return transpose(Matrix(
        ci.x * v.x + c, ci.x * v.y + s.z, ci.x * v.z - s.y, 0,
        ci.y * v.x - s.z, ci.y * v.y + c, ci.y * v.z + s.x, 0,
        ci.z * v.x + s.y, ci.z * v.y - s.x, ci.z * v.z + c, 0,
        0, 0, 0, 1
	));
}

// intersect ray with sphere to find
//  - the distance to the sphere
//  - and the point of intersection on the sphere
// http://viclw17.github.io/2018/07/16/raytracing-ray-sphere-intersection/
float intersect_ray_sphere(float3 origin, float3 direction, float3 center, float radius)
{
    // hit 지점 까지의 거리
    // 아 center 기준으로 radius 이내의 범위
    float3 oc = origin - center;
    float a = dot(direction, direction); // direction Square
    float b = 2. * dot(oc, direction);
    float c = dot(oc, oc) - radius * radius;
    float disc = b * b - 4. * a * c;
    if (disc < 0.)
    {
        // no intersection?
        return -1.;
    }
    else
    {
        return (-b - sqrt(disc)) / (2. * a);
    }
}

// void mainImage(out float4 fragColor, in float2 fragCoord)
PixelShaderOutput main(PixelShaderInput input)
{
    // TODO: 
    
    // 해당 방식은 (0.5, 0.5, -1.9) 에서 바라본 빌보드 판의 각 픽셀의 색상값을 출력함
    // 똑같이 FireballSphere에 레이트레이싱 기법으로 접근하는 것은 동일함
    // 그러나 기존의 방식은 고정된 시점에서 고정된 빌보드판에 대한 렌더링 이미지가 view 시점 변환으로 인해 camera의 변환의 역으로 움직이는 것
    // float3 eye = float3(0.5, 0.5, -1.9);
    // float3 dir = normalize(float3(input.texCoord.x, input.texCoord.y, 0.0) - eye);
    // float3 sphere_pos = float3(0.5, 0.5, 0.0);
    // float radiusScale = 1.0;
    // float currentTime = 1.0;
       
    // 그러나 해당방식은 시간을 멈춘다하더라도 동적임
    // camera 이동으로 인해 발생하는 eye의 변환된 pos와 빌보드의 변환된 pos를 기반으로 색상값을 추적함
    // shpere의 위치도 마찬가지
    // 여기서 posWorld.xyz는 각 픽셀의 월드좌표를 의미함 (레스터라이징)
    float3 eye = eyeWorld;
    float3 dir = normalize(input.posWorld.xyz - eye);
    float3 sphere_pos = input.center.xyz;
    float radiusScale = width; // 빌보드 크기에 비례하여 이미지가 커지게 만들기
    float currentTime = time + input.primID; // 이렇게 하면 VS에 입력된 세 버텍스 기준으로 형성된 Fireball이 서로 다른 움직임을 보임 (시차 발생)
    
    // 즉 기존 방식은 렌더링이 끝난 판이 내 시점 변환에 따라 껌딱지마냥 같이 움직이는 것 (월드에서 결정난 것이 그저 움직일 뿐임)
    // 변환된 방식은 이동으로 인하여 Ray의 dir이 달라짐
    // 따라서 스피어 형태로 매핑되어 고정되어 있는 것을 시점에 맞게 가져올 수 있는것
    
    float intensity = 0.;
    
    Matrix tex_mat = Matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
    Matrix wind_mat = Matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
    
    for (int i = 1; i < 10; ++i) // 나누기 때문에 i = 0 제외 
    {
        float dist = intersect_ray_sphere(eye, dir, sphere_pos, (0.4 - float(i) / 200.0) * radiusScale);

        if (dist > 0.0)
        {
            // 텍스쳐를 시간에 따라 회전시킴
            tex_mat = mul(tex_mat, rotate(radians(11.) * currentTime, normalize(float3(0.3, -0.7, 0.1))));
            wind_mat = mul(wind_mat, rotate(radians(25.) * currentTime, normalize(float3(1.0, 0.0, 0.0))));
            
            float3 hit_pos = eye + dir * dist;
            float3 normal = normalize(hit_pos - sphere_pos);
            normal = mul(float4(normal, 1.), mul(wind_mat, tex_mat)).xyz;
            
            float2 uv = float2(1.0 / float(i) * float2(atan2(normal.x, normal.z) / radians(90.0), normal.y));
            float alpha = g_texArray.Sample(g_sampler, float3(uv, 0)).r;
            intensity += step(1.0 - float(i) / 6.0, alpha) * 0.6 * alpha * max(0., dot(float3(0, 0, 1.), normal) + 1.0);
        }
    }
    
    float3 glow = fire_color(2.) * max(0., 1.3 - 1.8 * length(input.texCoord * 2.0 - 1.0));
    float3 color = fire_color(intensity);
    
    PixelShaderOutput output;
    output.pixelColor = float4(.09 * glow + 0.8 * color, 1.0);
    
    // clip((color.r + color.g + color.b) < 0.1 * 3.0 ? -1 : 1);
    clip(dot(output.pixelColor.rgb, float3(1.0, 1.0, 1.0)) - 0.1);
    // discard (버림)
    
    return output;
}
