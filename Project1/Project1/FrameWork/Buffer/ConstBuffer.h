#pragma once

class ConstantBuffer
{
protected:
    ConstantBuffer(void* data, UINT dataSize);
    ~ConstantBuffer();
 
    void Update();

public:
    void SetVSBuffer(UINT slot);
    void SetPSBuffer(UINT slot);
    void SetCSBuffer(UINT slot);

private:
    ID3D11Buffer* buffer;

    void* m_data;
    UINT m_dataSize;

    D3D11_MAPPED_SUBRESOURCE subResource;
};