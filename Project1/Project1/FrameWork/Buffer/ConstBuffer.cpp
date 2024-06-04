#include "Framework.h"

ConstantBuffer::ConstantBuffer(void* data, UINT dataSize)
    :m_data(data), m_dataSize(dataSize)
{
    //WVP constant_Buffer
    {
        D3D11_BUFFER_DESC buffer_Desc = {};
        buffer_Desc.Usage = D3D11_USAGE_DYNAMIC;
        buffer_Desc.ByteWidth = dataSize;             // sizeof(Vertex) == float(4 byte) *3 == 12 byte
        buffer_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;   // GPU�� ���� �� �ְ� �϶�
        buffer_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

        DEVICE->CreateBuffer(&buffer_Desc, nullptr, &buffer);
    }
}

ConstantBuffer::~ConstantBuffer()
{
    buffer->Release();
}

void ConstantBuffer::Update()
{
    // CPU-> GPU(RAM -> VRAM)���� �ű�� �۾�
    // �ӵ��� ������� ������ ���� ������Ʈ �ϴ°� �̰� ����
    DC->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
    memcpy(subResource.pData, m_data, m_dataSize);  // ������ , ���� , ������ ������ ->������ ������ Ʋ���� ������
    DC->Unmap(buffer, 0);
}


void ConstantBuffer::SetVSBuffer(UINT slot)
{
    Update();
    DC->VSSetConstantBuffers(slot, 1, &buffer);
}

void ConstantBuffer::SetPSBuffer(UINT slot)
{
    Update();
    DC->PSSetConstantBuffers(slot, 1, &buffer);
}

void ConstantBuffer::SetCSBuffer(UINT slot)
{
    Update();
    DC->CSSetConstantBuffers(slot, 1, &buffer);
}

