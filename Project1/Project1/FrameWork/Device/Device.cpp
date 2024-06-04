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
    // RefreshRate : 디스플레이 모드 갱신율 =/= FPS ==> Normerator / Denominator;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = hWnd;

    swapChainDesc.SampleDesc.Count = 1; // => 표본을 하나만 둠
    swapChainDesc.SampleDesc.Quality = 0;   // 방지 안함
    // Sample = 표본화 -> 확대시켰을때 pixel화 되는 것을 방지
    // ex. 미리 확대후 다시 축소 시키는 방법  || 표본을 여러개를 만들고 색을 조합 시키는 방법
    swapChainDesc.Windowed = true;  // 창모드 유무

    D3D11CreateDeviceAndSwapChain(  // device , device_context , swapChain 할당하는 것
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,   // SDK 나 API는 hardware로 한다.
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
    // 모든 pointer은 보두 8 byte를 가진다. -> 주소값을 받을껀데 어떤 형인지 모를떄 void* 를 많이 사용한다.
    // __uuidof => 자료 고유의 index를 준다.
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
