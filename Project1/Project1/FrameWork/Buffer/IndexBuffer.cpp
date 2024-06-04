#include "Framework.h"

IndexBuffer::IndexBuffer(void* data, UINT count)
    : m_offset(0)
{
    D3D11_BUFFER_DESC buffer_Desc = {};
    buffer_Desc.Usage = D3D11_USAGE_DEFAULT;
    buffer_Desc.ByteWidth = sizeof(UINT) * count;             // sizeof(Vertex) == float(4 byte) *3 == 12 byte
    buffer_Desc.BindFlags = D3D11_BIND_INDEX_BUFFER;   // GPU�� ���� �� �ְ� �϶�
 
    D3D11_SUBRESOURCE_DATA subData = {};
    subData.pSysMem = data; // �������� ù���� �ּҰ� -- data�� [0]�� data�� �� ������
 
    DEVICE->CreateBuffer(&buffer_Desc, &subData, &buffer);
}

IndexBuffer::~IndexBuffer()
{
    buffer->Release();
}

void IndexBuffer::IASet()
{
    DC->IASetIndexBuffer(buffer, DXGI_FORMAT_R32_UINT, 0);
}
