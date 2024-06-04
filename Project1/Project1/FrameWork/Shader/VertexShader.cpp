#include "Framework.h"

VertexShader::VertexShader(wstring file)
{
    this->file = file;

    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS || D3DCOMPILE_DEBUG;

    D3DCompileFromFile(file.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VS", "vs_5_0", flags, 0, &blob, nullptr);

    DEVICE->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &Shader);

    CreateInputLayout();
}

void VertexShader::CreateInputLayout()
{
    //IID -> interface ID 뒤에 나올꺼는 이런거임
    D3DReflect(blob->GetBufferPointer(), blob->GetBufferSize(),
        IID_ID3D11ShaderReflection, (void**)&reflection);

    D3D11_SHADER_DESC shader_Desc;
    reflection->GetDesc(&shader_Desc);

    vector<D3D11_INPUT_ELEMENT_DESC> layouts;

    for (UINT i = 0; i < shader_Desc.InputParameters; i++)
    {
        D3D11_SIGNATURE_PARAMETER_DESC param_desc;
        reflection->GetInputParameterDesc(i, &param_desc);

        D3D11_INPUT_ELEMENT_DESC elementDesc;
        elementDesc.SemanticName = param_desc.SemanticName;
        elementDesc.SemanticIndex = param_desc.SemanticIndex;
        elementDesc.InputSlot = 0;
        elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
        elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        elementDesc.InstanceDataStepRate = 0;

        if (param_desc.Mask == 1) {

            if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
                elementDesc.Format = DXGI_FORMAT_R32_UINT;
            else if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
                elementDesc.Format = DXGI_FORMAT_R32_SINT;
            else if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
                elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
        }
        else if (param_desc.Mask < 2) {

            if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
                elementDesc.Format = DXGI_FORMAT_R32_UINT;
            else if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
                elementDesc.Format = DXGI_FORMAT_R32_SINT;
            else if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
                elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
        }
        else if (param_desc.Mask < 4) {

            if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
            else if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
            else if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
                elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
        }
        else if (param_desc.Mask < 8) {

            if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
            else if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
            else if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
        }
        else if (param_desc.Mask < 16) {

            if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
            else if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
            else if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
        }

        string temp = param_desc.SemanticName;
        if (temp == "POSITION")
        {
            elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
        }

        int n = temp.find_first_of("_");

        temp = temp.substr(0, n); //- > VertexInput 에서 INSTANCE_TRANSFORM 에서 INSTANCE만 가져오기
        if (temp == "INSTANCE")
        {
            elementDesc.InputSlot = 1;
            elementDesc.InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
            elementDesc.InstanceDataStepRate = 1;
        }

        layouts.push_back(elementDesc);
    }

    DEVICE->CreateInputLayout(layouts.data(), layouts.size(),
        blob->GetBufferPointer(), blob->GetBufferSize(),
        &input_Layout);
}

VertexShader::~VertexShader()
{
    Shader->Release();
    input_Layout->Release();

    blob->Release();
}

void VertexShader::Set()
{
    DC->IASetInputLayout(input_Layout);
    DC->VSSetShader(Shader, nullptr, 0);
}
