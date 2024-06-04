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

	// map -> hash(주소값 같은 것)을 정리한 map 
	// unordered_map -> 정리 x
	static unordered_map<wstring, Texture*> textures;
};