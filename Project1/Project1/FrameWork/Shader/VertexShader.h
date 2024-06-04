#pragma once

class VertexShader : public Shader
{
public:
	VertexShader(wstring file);
	~VertexShader();

	void Set();

private:
	void CreateInputLayout();

private:
	ID3D11VertexShader* Shader;
	ID3D11InputLayout* input_Layout;

	ID3DBlob* blob;

	// shader의 정보를 빼오는 애
	ID3D11ShaderReflection* reflection;
};