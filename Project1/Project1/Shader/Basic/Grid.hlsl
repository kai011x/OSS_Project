// HLSL  =  High Level Shader language
// Shader : GPU�� �ٷ�� ���
// Shade(ä��) + er -> ä���� �ٷ�� ��

// Sementic : �Ű����� �� ��ȯ�� ������ ��� ������� �̸� ���̴� ��
// SV  : system value �̰� �Ⱥ��̸� Pixel shader�� �޾ƹ���

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

// ����ϴ� cbuffer �������
// cbuffer WVP : register(b0)  // constant buffer -> ���������� ��û �ٲ����� ����� ���
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

float4 PS(PixelInput input) : SV_TARGET // ���� ����
{
    return input.color;

}