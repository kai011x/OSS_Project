#pragma once

class Texture
{
private:
	Texture(ID3D11ShaderResourceView* srv , ScratchImage& image);
	~Texture();

public:
	static Texture* Add(wstring file);
	static void Delete();

	void PSSet(UINT slot);
	
	void ReadPixels(vector<Float4>& outPixels);

	UINT Width() { return image.GetMetadata().width; }
	UINT Height() { return image.GetMetadata().height; }

	ID3D11ShaderResourceView*& GetSRV() { return srv; }

	wstring GetFile() { return file; }
private:
	wstring file;

	ScratchImage image;
	ID3D11ShaderResourceView* srv;

	// map -> hash(�ּҰ� ���� ��)�� ������ map 
	// unordered_map -> ���� x
	static unordered_map<wstring, Texture*> textures;
};