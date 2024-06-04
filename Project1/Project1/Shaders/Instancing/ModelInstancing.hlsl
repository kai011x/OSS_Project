#include "../VertexHeader.hlsli"
#include "../PixelHeader.hlsli"

struct PixelInput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
    float3 viewDir : VIEWDIR;
};


PixelInput VS(VertexInstancing input)
{
    PixelInput output;
    
    matrix trasnform = input.transform;
    
    output.pos = mul(input.pos, trasnform);
    
    output.viewDir = normalize(output.pos.xyz - invView._41_42_43);
    
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);

    output.uv = input.uv;
    
    output.normal = mul(input.normal, (float3x3) trasnform);
    output.tangent = mul(input.tangent, (float3x3) trasnform);
    output.binormal = cross(output.normal, output.tangent);
    
    return output;
}

float4 PS(PixelInput input) : SV_TARGET // 색의 영역
{
    float4 albedo = float4(1, 1, 1, 1);
    
    if (hasDM0)
        albedo = diffuseMap.Sample(samp, input.uv);
    
    float3 normal = normalize(input.normal);

    if (hasNM0)
    {
        float3 T = normalize(input.tangent); // x축
        float3 B = normalize(input.binormal); // y축
        float3 N = normalize(input.normal); //z축에 해당
        float3x3 TBN = float3x3(T, B, N);

        float4 normalMapping = normalMap.Sample(samp, input.uv);
        normal = normalMapping.rgb * 2.0f - 1.0f; // 0~1 -> -1 ~ 1로 바꾸기
        normal = normalize(mul(normal, TBN));
    }
    
    float3 light = normalize(lightDir);
    
    float diffuse = saturate(dot(normal, -light));

    float4 specular = 0;
    if (diffuse > 0.0f)  // 빛이 들어 온다면
    {
        float3 reflection = normalize(reflect(light, normal));
        specular = saturate(dot(-reflection, input.viewDir));
        
        float4 specularIntensity = float4(1, 1, 1, 1);
        if (hasSM0)
            specularIntensity = specularMap.Sample(samp, input.uv);
        
        // ^ = pow
        specular = pow(specular, shininess) * specularIntensity;
    }
    
    float4 diffuseColor = albedo * diffuse * mDiffuse;
    float4 specularColor = specular * mSpecular;
    float4 ambientColor = albedo * ambient * mAmbient;
    
    return diffuseColor + specularColor + ambientColor;

}