#include "Framework.h"

SamplerState::SamplerState()
{
    // LINEAR -> 3D 안티에이징 / POINT -> 픽셀화
    desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;    // -> UV가 넘쳤을떄 어캄? WRAP -> 반복해서 복붙하삼
    desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;    // MIRROR -> 좌우 반경으로 복붙하삼   CLAMP -> 하나만 그려
    desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    desc.MinLOD = 0;
    desc.MaxLOD = D3D11_FLOAT32_MAX;
    // LOD(Level of Detail) -> 카메라에 따라서 얼마나 묘사할꺼임?

    Changed();
}

SamplerState::~SamplerState()
{
    state->Release();
}

void SamplerState::PSSetState(UINT slot)
{
    DC->PSSetSamplers(slot, 1, &state);
}

void SamplerState::Fillter(D3D11_FILTER value)
{
    desc.Filter = value;
    Changed();
}

void SamplerState::Changed()
{
    if (state != nullptr)
        state->Release();

    DEVICE->CreateSamplerState(&desc, &state);
}
