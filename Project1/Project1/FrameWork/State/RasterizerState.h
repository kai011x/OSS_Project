#pragma once


class RasterizerState
{
public:
	RasterizerState();
	~RasterizerState();

	void SetState(UINT slot = 0);

	void FillMode(D3D11_FILL_MODE value);
	void FrontCountClockWise(bool value);

	void Changed();

private:
	D3D11_RASTERIZER_DESC desc = {};
	ID3D11RasterizerState* state = nullptr;


};

