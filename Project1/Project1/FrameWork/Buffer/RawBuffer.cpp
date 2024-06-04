#include "Framework.h"

Rawbuffer::Rawbuffer(UINT byteWidth)
	: byteWidth(byteWidth)
{
	CreateOutput();
	CreateUAV();
	CraeateResult();
}

Rawbuffer::~Rawbuffer()
{
	output->Release();
	uav->Release();
	result->Release();
}

void Rawbuffer::Copy(void* data, UINT size)
{
	DC->CopyResource(result, output);

	D3D11_MAPPED_SUBRESOURCE subResource;
	DC->Map(result, 0, D3D11_MAP_READ, 0, &subResource);	// 주소값 열기
	memcpy(data, subResource.pData, size);	// 값 넣기
	DC->Unmap(result, 0);

}

void Rawbuffer::CreateOutput()
{
	ID3D11Buffer* buffer;

	D3D11_BUFFER_DESC buffer_Desc = {};
	buffer_Desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_Desc.ByteWidth = byteWidth;            // sizeof(Vertex) == float(4 byte) *3 == 12 byte
	buffer_Desc.BindFlags = D3D11_BIND_UNORDERED_ACCESS;   // GPU에 읽을 수 있게 하라
	buffer_Desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;

	DEVICE->CreateBuffer(&buffer_Desc, nullptr, &buffer);

	output = (ID3D11Resource*)buffer;
}

void Rawbuffer::CreateUAV()
{
	ID3D11Buffer* buffer = (ID3D11Buffer*)output;

	D3D11_BUFFER_DESC bufferDesc = {};
	buffer->GetDesc(&bufferDesc);

	D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
	uavDesc.Format = DXGI_FORMAT_R32_TYPELESS;
	uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
	uavDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW;
	uavDesc.Buffer.NumElements = byteWidth / 4;

	DEVICE->CreateUnorderedAccessView(buffer, &uavDesc, &uav);

}

void Rawbuffer::CraeateResult()
{
	ID3D11Buffer* buffer;

	D3D11_BUFFER_DESC buffer_Desc = {};
	((ID3D11Buffer*)output)->GetDesc(&buffer_Desc);
	buffer_Desc.Usage = D3D11_USAGE_STAGING;
	buffer_Desc.BindFlags = 0;  
	buffer_Desc.MiscFlags = 0;
	buffer_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

	DEVICE->CreateBuffer(&buffer_Desc, nullptr, &buffer);

	result = (ID3D11Resource*)buffer;
}
