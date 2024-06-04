#include "../../VertexHeader.hlsli"
#include "../../PixelHeader.hlsli"

cbuffer Camera_Position_Buffer : register(b9)
{
    float3 cameraPos;
    float lenght;
}

struct PixelInput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
    
    float4 worldPos : POSITION;
};

PixelInput VS(VertexUV input)
{
    PixelInput output;
    output.pos = mul(input.pos, world);
    output.worldPos = input.pos;
    
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);

    output.uv = input.uv;

    return output;
}

float4 PS(PixelInput input) : SV_TARGET // 색의 영역
{
    return diffuseMap.Sample(samp, input.uv);
}