// HLSL  =  High Level Shader language
// Shader : GPU를 다루는 언어
// Shade(채도) + er -> 채도를 다루는 애

// Sementic : 매개변수 및 반환값 정보를 어떨게 사용할지 이름 붙이는 것
// SV  : system value 이거 안붙이면 Pixel shader이 받아버림

cbuffer WorldBuffer : register(b0)
{
    matrix world;
}

cbuffer ViewBuffer : register(b1)
{
    matrix view;
}

cbuffer ProjectionBuffer : register(b2)
{
    matrix projection;
}

// 대신하는 cbuffer 만들어짐
// cbuffer WVP : register(b0)  // constant buffer -> 실질적으로 엄청 바꾸지만 상수로 취금
// {
//     matrix world;
//     matrix view;
//     matrix projection;
// }

struct VertexInput
{
    float4 pos : POSITION;
    float4 color : COLOR;
};


struct PixelInput
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
};


PixelInput VS(VertexInput input)
{
	PixelInput output;
	output.pos = mul(input.pos, world);
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);

	output.color = input.color;

	return output;
}

float4 PS(PixelInput input) : SV_TARGET // 색의 영역
{
    return input.color;

}