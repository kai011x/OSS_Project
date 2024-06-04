#pragma once

class GameObject : public Transform
{
public:
    GameObject();
    GameObject(string Load_File , wstring shaderFile,string ID);
	GameObject(wstring shaderFile);
    virtual ~GameObject();

    virtual void Render();
    virtual void InstancingRender(UINT instanceCount);
  
    Material* Getmaterial() { return material; }

protected:
    Material* material;
    Mesh* mesh;

    MatrixBuffer* worldBuffer;
    vector<UINT> indices;
};
