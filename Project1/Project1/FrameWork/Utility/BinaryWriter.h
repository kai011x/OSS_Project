#pragma once

class BinaryWriter
{
public:
    BinaryWriter(wstring filePath);
    BinaryWriter(string filePath);
    ~BinaryWriter();

    void Int(int data);
    void UInt(UINT data);
    void Float(float data);
    void String(string data);
    void WString(wstring data);

    void Vector(class Vector3 data);
    void Matrix(XMMATRIX data);
    void Float4(XMFLOAT4 data);

    void Byte(void* data, UINT dataSize);

private:
    HANDLE file;
    DWORD size = 0;
};