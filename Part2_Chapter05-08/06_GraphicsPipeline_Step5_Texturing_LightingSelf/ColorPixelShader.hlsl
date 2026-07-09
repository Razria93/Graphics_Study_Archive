Texture2D g_texture0 : register(t0);
Texture2D g_texture1 : register(t1);
SamplerState g_sampler : register(s0);

cbuffer LightConstantBuffer : register(b0)
{
    float3 lightPos;             
    float3 lightAmbient;    
    float3 lightDiffuse;    
    float3 lightSpecular;   

    float kc;               
    float kl;               
    float kq;               
    float radius;           
    float3 viewPos;
};

cbuffer MaterialConstantBuffer : register(b1)
{
    float3 matAmbient;      
    float3 matDiffuse;      
    float3 matSpecular;     

    float shininess;        

    float ks;               
    float kd;               
};

struct PixelShaderInput
{
    float4 projPos : SV_POSITION;
    float4 worldPos : WORLDPOSITION;
    float3 normal : NORMAL;
    float2 texcoord : TEXCOORD;
};
float4 main(PixelShaderInput input) : SV_TARGET
{
    float3 normalDir = normalize(input.normal);
    float3 lightVec = lightPos - input.worldPos.xyz;
    float3 lightDir = normalize(lightVec); 
    float distToLight = length(lightVec);
    float3 viewVec = viewPos - input.worldPos.xyz;
    float3 viewDir = normalize(viewVec);
    float4 text = g_texture0.Sample(g_sampler, input.texcoord);
    float4 ambient = float4(lightAmbient, 1.0) * float4(matAmbient, 1.0) * text;
    float diffuseRatio = max(0.0, dot(normalDir, lightDir));
    float4 diffuse = float4(lightDiffuse, 1.0) * float4(matDiffuse, 1.0) * diffuseRatio * text;
    float3 halfDir = normalize(lightDir + viewDir);
    float hdotn = max(0.0, dot(halfDir, normalDir));
    float specularRatio = max(0.0, pow(hdotn, shininess));
    float4 specular = float4(lightSpecular, 1.0) * (float4(matSpecular, 1.0) * specularRatio) * text;
    float attenuation = 1.0f / (kc + kl * distToLight + kq * distToLight * distToLight);
    float4 color = ambient + (diffuse + specular) * attenuation;
    return color;
}
