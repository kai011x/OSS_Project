#include "Framework.h"

VertexBuffer::VertexBuffer(void* data, UINT stride, UINT count)
    :m_stride(stride), m_offset(0)
{
	// vertex_Buffer
 
    D3D11_BUFFER_DESC buffer_Desc = {};
    buffer_Desc.Usage = D3D11_USAGE_DEFAULT;
    buffer_Desc.ByteWidth = stride *count;             // sizeof(Vertex) == float(4 byte) *3 == 12 byte
    buffer_Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;   // GPU�� ���� �� �ְ� �϶�
 
    D3D11_SUBRESOURCE_DATA subData = {};
    subData.pSysMem = data; // �������� ù���� �ּҰ� -- data�� [0]�� data�� �� ������
 
    DEVICE->CreateBuffer(&buffer_Desc, &subData, &buffer);
 
}

VertexBuffer::~VertexBuffer()
{
    buffer->Release();
}

void VertexBuffer::IASet(D3D11_PRIMITIVE_TOPOLOGY type)
{
    DC->IASetVertexBuffers(0, 1, &buffer, &m_stride, &m_offset);
    DC->IASetPrimitiveTopology(type);
}

void VertexBuffer::IASet(UINT slot, D3D11_PRIMITIVE_TOPOLOGY type)
{
    DC->IASetVertexBuffers(slot, 1, &buffer, &m_stride, &m_offset);
    DC->IASetPrimitiveTopology(type);
}

void VertexBuffer::Update(void* data, UINT count)
{
    DC->UpdateSubresource(buffer, 0, nullptr, data, m_stride, count);
}
