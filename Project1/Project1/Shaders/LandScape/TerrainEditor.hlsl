// TerrainEditor.hlsl
#include "../VertexHeader.hlsli"
#include "../PixelHeader.hlsli"

struct VertexInput
{
    float4 pos : POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float4 alpha : ALPHA;
};

struct PixelInput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
    float3 viewDir : VIEWDIR;
    float3 worldPos : POSITION;
    float4 alpha : ALPHA;
};


PixelInput VS(VertexInput input)
{
    PixelInput output;
    output.pos = mul(input.pos, world);
    
    output.worldPos = output.pos;
    
    output.viewDir = normalize(output.pos.xyz - invView._41_42_43);
    
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);

    output.uv = input.uv;
    
    output.normal = mul(input.normal, (float3x3) world);
    output.tangent = mul(input.tangent, (float3x3) world);
    output.binormal = cross(output.normal, output.tangent);
    
    output.alpha = input.alpha;

    return output;
}

cbuffer BrushBuffer : register(b10)
{
    int type;
    float3 PickingPos;
    
    float range;
    float3 color;

    int camera_Use;
    float3 camera_Angle;
}

float3 BrushColor(float3 pos)
{
    float3 pos_c = pos;
    float PI = 3.141592;

    if (camera_Use != 0)
    {
        pos_c.x = (pos.x - PickingPos.x) * cos(camera_Angle.y) - (pos.z - PickingPos.z) * sin(camera_Angle.y) + PickingPos.x;
        pos_c.z = (pos.z - PickingPos.z) * cos(camera_Angle.y) + (pos.x - PickingPos.x) * sin(camera_Angle.y) + PickingPos.z;
    }

    if(type == 0 )  // 원
    {
       float2 direction = pos.xz - PickingPos.xz;
       float distance = length(direction);
       if(distance <= range)
           return color;
    }
    else if (type == 1)  // 사각형
    {
        if ((PickingPos.x - range * 0.5f < pos_c.x && PickingPos.x + range * 0.5f > pos_c.x) &&
            (PickingPos.z - range * 0.5f < pos_c.z && PickingPos.z + range * 0.5f > pos_c.z))
        {
            return color;
        }
    }
    else if (type == 2) //목표 : 정삼각형
    {
        if ((PickingPos.x - tan(PI / 6) * (PickingPos.z + range * 0.5 - pos_c.z) < pos_c.x &&
            (PickingPos.x + tan(PI / 6) * (PickingPos.z + range * 0.5 - pos_c.z) > pos_c.x)) &&
            (PickingPos.z - range * 0.5f < pos_c.z && PickingPos.z + range * 0.5f > pos_c.z))
        {
            return color;
        }
    }
    else if (type == 3) // 목표 : 별모양
    {
        for (int i = 0; i < 5; i++)
        {
            float3 pos_r;
            pos_r.x = (pos_c.x - PickingPos.x) * cos(i * 2 * PI / 5) - (pos_c.z - PickingPos.z) * sin(i * 2 * PI / 5) + PickingPos.x;
            pos_r.z = (pos_c.z - PickingPos.z) * cos(i * 2 * PI / 5) + (pos_c.x - PickingPos.x) * sin(i * 2 * PI / 5) + PickingPos.z;

            if ((PickingPos.x - tan(PI / 6) * abs(PickingPos.z + range * 0.5f - pos_r.z) < pos_r.x) &&
                (PickingPos.x + tan(PI / 6) * abs(PickingPos.z + range * 0.5f - pos_r.z) > pos_r.x) &&
                (PickingPos.z < pos_r.z && PickingPos.z + range * 0.5f > pos_r.z))
            {
                return color;
            }
        }
    }
    else if (type == 4) // 목표 : 하트
    {
        float2 direction = pos_c.xz - PickingPos.xz;  // pickingPos 에서 pos값으로 가는 벡터
        float distance = length(direction);         // 그 벡터의 길이

        float theta = acos(direction.y / distance);

        if (distance <= range * sqrt(theta / PI))
            return color;
    }
    return float3(0, 0, 0);
}

Texture2D alphaMap : register(t10);
Texture2D secondDiffuseMap : register(t11);
Texture2D thirdDiffuseMap : register(t12);

Texture2D secondSpecualrMap : register(t13);
Texture2D thirdSpecualrMap : register(t14);

Texture2D secondNormalMap : register(t15);
Texture2D thirdNormalMap : register(t16);


float4 PS(PixelInput input) : SV_TARGET // 색의 영역
{
    float4 albedo = float4(1, 1, 1, 1);
    
    if (hasDM0)
        albedo = diffuseMap.Sample(samp, input.uv);
   
    float4 alpha = input.alpha;

   if (make_mode == 0)
       alpha = alphaMap.Sample(samp, input.uv);

    if (hasDM1)
    {
        float4 second = secondDiffuseMap.Sample(samp, input.uv);
        albedo = lerp(albedo, second, alpha.r);
    }
    
    if (hasDM2)
    {
        float4 third = thirdDiffuseMap.Sample(samp, input.uv);
        albedo = lerp(albedo, third, alpha.g);
    }
    
    float3 normal = normalize(input.normal);

    float3 T = normalize(input.tangent); // x축
    float3 B = normalize(input.binormal); // y축
    float3 N = normalize(input.normal); //z축에 해당
    float3x3 TBN = float3x3(T, B, N);

    if (hasNM0)
    {
        float4 normalMapping = normalMap.Sample(samp, input.uv);
        normal = normalMapping.rgb * 2.0f - 1.0f; // 0~1 -> -1 ~ 1로 바꾸기
    }
    
    if (hasNM1)
    {
        float4 second_normal = secondNormalMap.Sample(samp, input.uv);
        normal = lerp(normal, second_normal, alpha.r);
    }
    
    if (hasNM2)
    {
        float4 third_normal = thirdNormalMap.Sample(samp, input.uv);
        normal = lerp(normal, third_normal, alpha.g);
    }
    
    if (hasNM0 == 1 || hasNM1 == 1 || hasNM2 == 1)
        normal = normalize(mul(normal, TBN));

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
        
        if (hasSM1)
        {
            float4 second_spec = secondSpecualrMap.Sample(samp, input.uv);
            specularIntensity = lerp(specularIntensity, second_spec, alpha.r);
        }
    
        if (hasSM2)
        {
            float4 third_spec = thirdSpecualrMap.Sample(samp, input.uv);
            specularIntensity = lerp(specularIntensity, third_spec, alpha.g);
        }

        // ^ = pow
        specular = pow(specular, shininess) * specularIntensity;
    }
    
    float4 diffuseColor = albedo * diffuse * mDiffuse;
    float4 specularColor = specular * mSpecular;
    float4 ambientColor = albedo * ambient * mAmbient;
    
    float4 brushColor = float4(BrushColor(input.worldPos), 1.0f);
    
    return diffuseColor + specularColor + ambientColor + brushColor;
}