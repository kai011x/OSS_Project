#include "Framework.h"

SamplerState::SamplerState()
{
    // LINEAR -> 3D ��Ƽ����¡ / POINT -> �ȼ�ȭ
    desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;    // -> UV�� �������� ��į? WRAP -> �ݺ��ؼ� �����ϻ�
    desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;    // MIRROR -> �¿� �ݰ����� �����ϻ�   CLAMP -> �ϳ��� �׷�
    desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    desc.MinLOD = 0;
    desc.MaxLOD = D3D11_FLOAT32_MAX;
    // LOD(Level of Detail) -> ī�޶� ���� �󸶳� �����Ҳ���?

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
