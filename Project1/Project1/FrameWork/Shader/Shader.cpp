#include "Framework.h"

unordered_map< wstring, Shader*> Shader::shaders;

VertexShader* Shader::AddVS(wstring file)
{
    if (file.length() == 0) return nullptr;

    wstring key = file + L"VS";

    if (shaders.count(key) > 0)
        return (VertexShader*)shaders[key];

    shaders[key] = new VertexShader(file);

    return (VertexShader*)shaders[key];
}

PixelShader* Shader::AddPS(wstring file)
{
    if (file.length() == 0) return nullptr;

    wstring key = file + L"PS";

    if (shaders.count(key) > 0)
        return (PixelShader*)shaders[key];

    shaders[key] = new PixelShader(file);

    return (PixelShader*)shaders[key];
}

ComputeShader* Shader::AddCS(wstring file)
{
    if (file.length() == 0) return nullptr;

    wstring key = file + L"CS";

    if (shaders.count(key) > 0)
        return (ComputeShader*)shaders[key];

    shaders[key] = new ComputeShader(file);

    return (ComputeShader*)shaders[key];
}

void Shader::Delete()
{
    for (pair<wstring, Shader*> shader : shaders)
        delete shader.second;
}