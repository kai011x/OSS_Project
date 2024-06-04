#include "../VertexHeader.hlsli"
#include "../PixelHeader.hlsli"

struct PixelInput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
};


PixelInput VS(VertexUV input)
{
    PixelInput output;
    output.pos = mul(input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);

    output.uv = input.uv;

    return output;
}

cbuffer ColorBuffer : register(b0)
{
    float4 color;
}

// Texture2D diffuseMap : register(t0);

float4 PS(PixelInput input) : SV_TARGET // ���� ����
{
    return diffuseMap.Sample(samp,input.uv) *mDiffuse;
}