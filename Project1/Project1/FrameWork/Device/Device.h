#pragma once

class Device : public Singleton<Device>
{
public:
	Device();
	~Device();

	void Clear();
	void Present();
	
	ID3D11Device* GetDevice() { return device; }
	ID3D11DeviceContext* GetDeviceContext() { return device_Context; }

private:
	void CreateDeviceAndSwapChian();
	void CreateBuffer();

private:

	ID3D11Device* device;                       // CPU
	ID3D11DeviceContext* device_Context;        // GPU

	IDXGISwapChain* swapChain;                  // back_buffer����
	ID3D11RenderTargetView* renderTargetView;   // VRem Back Buffer ����

	ID3D11DepthStencilView* depthStencilView;	// VRem ���̹��� �޸� ����

};