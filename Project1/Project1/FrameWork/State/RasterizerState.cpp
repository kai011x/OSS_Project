#include "Framework.h"

RasterizerState::RasterizerState()
{
    desc.FillMode = D3D11_FILL_SOLID;
    desc.CullMode = D3D11_CULL_BACK;

    Changed();
}

RasterizerState::~RasterizerState()
{
    state->Release();
}


void RasterizerState::SetState(UINT slot)
{
    DC->RSSetState(state);
}

void RasterizerState::FillMode(D3D11_FILL_MODE value)
{
    desc.FillMode = value;

    Changed();
}

void RasterizerState::FrontCountClockWise(bool value)
{
    desc.FrontCounterClockwise = value;

    Changed();
}

void RasterizerState::Changed()
{
    if (state != nullptr)
        state->Release();

    DEVICE->CreateRasterizerState(&desc, &state);
}
