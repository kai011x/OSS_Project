#include "../../VertexHeader.hlsli"
#include "../../PixelHeader.hlsli"

cbuffer Camera_Position_Buffer : register(b9)
{
    float3 cameraPos;
    float lenght;
}

cbuffer MosterLightBuffer : register(b8)
{
    float4 monster_Pos[3];
}

struct PixelInput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
    float4 worldPos : POSITION;
    float3 viewDir : VIEWDIR;
};


PixelInput VS(VertexUVNormalTangent input)
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
   
    return output;
}

float distance_light4D_by_3D(float4 pos1, float3 pos2)
{
    float distance = sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2) + pow(pos1.z - pos2.z, 2));
    
    return distance;
}

float distance_light4D_to_3D(float4 pos1, float4 pos2)
{
    float distance = sqrt(pow(pos1.x - pos2.x, 2) +pow(pos1.y - pos2.y, 2) +pow(pos1.z - pos2.z, 2));
    return distance;
}

float4 Light_Regulate(float4 color, float4 inputWPos , float3 target_pos, float lenght)
{
    float distance_to_camera = distance_light4D_by_3D(inputWPos, target_pos);
    float4 color_result = color;
    if (distance_to_camera > lenght)
    {
        color_result *= lenght / (1.7f * distance_to_camera);
    }
    if (distance_to_camera > 2 * lenght)
    {
        color_result *= 0;
    }
    
    return color_result;
}

float4 Light_Regulate(float4 color, float4 inputWPos, float4 target_pos, float lenght)
{
    float distance_to_camera = distance_light4D_to_3D(inputWPos, target_pos);
    float4 color_result = color;
    if (distance_to_camera > lenght)
    {
        color_result *= lenght / (distance_to_camera);
    }
    if (distance_to_camera > 2 * lenght)
    {
        color_result *= 0;
    }
    
    return float4(1, 1, 1, 1) - color_result;
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
    
    float3 light_Dir;
    light_Dir.x = input.worldPos.x - cameraPos.x;
    light_Dir.y = input.worldPos.y - cameraPos.y;
    light_Dir.z = input.worldPos.z - cameraPos.z;
    float3 light = normalize(normalize(light_Dir));
    
    float diffuse = saturate(dot(normal, -light));
    
    float distance_to_camera = distance_light4D_by_3D(input.worldPos, cameraPos);
    
    float4 camera_light = { 1, 1, 1, 1 };
    camera_light = Light_Regulate(camera_light, input.worldPos, cameraPos, lenght);
    
    float4 monster_color = { 0.5f, 0.5f, 0.5f, 1 };

    for (int i = 0; i < 3; i++)
    {
        if (monster_Pos[i].w == 1)
        {
            float4 monster_color_temp = { 1, 1, 1, 1 };
            monster_color_temp[i] = 0;
            monster_color_temp = Light_Regulate(monster_color_temp, input.worldPos, monster_Pos[i], 20);
            
            monster_color *= monster_color_temp;

        }
    }
    
    
    float4 diffuseColor = albedo * diffuse * mDiffuse * camera_light * monster_color;
    float4 ambientColor = albedo * ambient * mAmbient;
    
    return diffuseColor + ambientColor;

}