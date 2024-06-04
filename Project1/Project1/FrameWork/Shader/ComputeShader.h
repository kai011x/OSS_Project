#pragma once

class ComputeShader : public Shader
{
public:
	ComputeShader(wstring file);
	~ComputeShader();

	void Set();

private:
	ID3D11ComputeShader* shader;
	ID3DBlob* blob;
};