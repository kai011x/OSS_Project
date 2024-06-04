#pragma once

class Rawbuffer
{
public:
	Rawbuffer(UINT byteWidth);
	~Rawbuffer();

	void Copy(void* data, UINT size);

	ID3D11UnorderedAccessView*& GetUAV() { return uav; }
private:
	void CreateOutput();
	void CreateUAV();
	void CraeateResult();

private:
	ID3D11Resource* output; // GPU -> output
	ID3D11UnorderedAccessView* uav;	

	ID3D11Resource* result;	// result -> CPU

	UINT byteWidth;

};
