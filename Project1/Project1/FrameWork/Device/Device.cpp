#include "Framework.h"

Device::Device()
{
	CreateDeviceAndSwapChian();
    CreateBuffer();
}

Device::~Device()
{
    device->Release();
    device_Context->Release();

    swapChain->Release();
    renderTargetView->Release();

    depthStencilView->Release();
}

void Device::Clear()
{
    float clearColor[4] = { 0.1f , 0.1f , 0.1f , 1.0f };
    device_Context->ClearRenderTargetView(renderTargetView, clearColor);
    device_Context->ClearDepthStencilView(depthStencilView,
        D3D11_CLEAR_DEPTH, 1, 0);
}

void Device::Present()
{
    swapChain->Present(0, 0);
}

void Device::CreateDeviceAndSwapChian()
{
    UINT width = WIN_WIDTH;
    UINT height = WIN_HEIGHT;

    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferDesc.Width = width;
    swapChainDesc.BufferDesc.Height = height;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // U = Usinged Norm = 0 ~ 1
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 60;
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 1;
    // RefreshRate : ���÷��� ��� ������ =/= FPS ==> Normerator / Denominator;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = hWnd;

    swapChainDesc.SampleDesc.Count = 1; // => ǥ���� �ϳ��� ��
    swapChainDesc.SampleDesc.Quality = 0;   // ���� ����
    // Sample = ǥ��ȭ -> Ȯ��������� pixelȭ �Ǵ� ���� ����
    // ex. �̸� Ȯ���� �ٽ� ��� ��Ű�� ���  || ǥ���� �������� ����� ���� ���� ��Ű�� ���
    swapChainDesc.Windowed = true;  // â��� ����

    D3D11CreateDeviceAndSwapChain(  // device , device_context , swapChain �Ҵ��ϴ� ��
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,   // SDK �� API�� hardware�� �Ѵ�.
        0,
        D3D11_CREATE_DEVICE_DEBUG,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &swapChainDesc,
        &swapChain,
        &device,
        nullptr,
        &device_Context
    );

}

void Device::CreateBuffer()
{
      ID3D11Texture2D* backBuffer;
    // ��� pointer�� ���� 8 byte�� ������. -> �ּҰ��� �������� � ������ �𸦋� void* �� ���� ����Ѵ�.
    // __uuidof => �ڷ� ������ index�� �ش�.
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

    device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);
    backBuffer->Release();

    ID3D11Texture2D* depthBuffer;

    D3D11_TEXTURE2D_DESC depthDesc = {};
    depthDesc.Width = WIN_WIDTH;
    depthDesc.Height = WIN_HEIGHT;
    depthDesc.MipLevels = 1;
    depthDesc.ArraySize = 1;
    depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthDesc.SampleDesc.Count = 1;
    depthDesc.Usage = D3D11_USAGE_DEFAULT;
    depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

    device->CreateTexture2D(&depthDesc, nullptr, &depthBuffer);

    D3D11_DEPTH_STENCIL_VIEW_DESC depthViewDesc = {};
    depthViewDesc.Format = depthDesc.Format;
    depthViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

    device->CreateDepthStencilView(depthBuffer, &depthViewDesc, &depthStencilView);

    device_Context->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

}
