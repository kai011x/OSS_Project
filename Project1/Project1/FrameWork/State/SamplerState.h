#pragma once

class SamplerState
{
public:
	SamplerState();
	~SamplerState();

	void PSSetState(UINT slot = 0);

	void Fillter(D3D11_FILTER value);

	void Changed();

private:
	D3D11_SAMPLER_DESC desc = {};
	ID3D11SamplerState* state = nullptr;


};

