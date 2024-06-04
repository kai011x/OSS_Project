// SpecularLight
// 직접광(난반사 : diffuse) + (정반사 : specular)
// 간접광(ambient)

cbuffer WorldBuffer : register(b0)
{
    matrix world;
}

cbuffer ViewBuffer : register(b1)
{
    matrix view;
    matrix invView;
}

cbuffer ProjectionBuffer : register(b2)
{
    matrix projection;
}

struct VertexInput
{
    float4 pos : POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
};


struct PixelInput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 viewDir : VIEWDIR;
};


PixelInput VS(VertexInput input)
{
    PixelInput output;
    output.pos = mul(input.pos, world);
    
    output.viewDir = normalize(output.pos.xyz - invView._41_42_43);
    
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);

    output.uv = input.uv;
    
    output.normal = mul(input.normal, (float3x3) world);

    return output;
}

Texture2D diffuseMap : register(t0);
Texture2D specularMap : register(t1);

SamplerState samp : register(s0);

cbuffer LightBuffer : register(b1)
{
    float3 lightDir;
    float shininess;
    
    float4 ambient;
}


float4 PS(PixelInput input) : SV_TARGET // 색의 영역
{
    float4 albedo = diffuseMap.Sample(samp, input.uv);
    float3 normal = normalize(input.normal);
    float3 light = normalize(lightDir);
    
    float diffuse = saturate(dot(normal, -light));
    
    float4 specular = 0;
    if(diffuse > 0.0f)  // 빛이 들어 온다면
    {
        float3 reflection = normalize(reflect(light, normal));
        specular = saturate(dot(-reflection, input.viewDir));
        
        float4 specularIntensity = specularMap.Sample(samp, input.uv);
        
        // ^ = pow
        specular = pow(specular, shininess) * specularIntensity;
        
    }
    
    float4 diffuseColor = albedo * diffuse;
    float4 ambientColor = albedo * ambient;
    float4 specularColor = specular;
    
    return diffuseColor + specularColor + ambientColor;
}