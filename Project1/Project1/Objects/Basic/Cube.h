#pragma once
#include "FrameWork/Render/Material.h"

class Cube : public GameObject
{
private:
    typedef VertexUVNormalTangent VertexType;

public:
    Cube(Vector3 size);
    ~Cube();

    void Render();
    void InstancingRender(UINT instanceCount);
    void Update_En(char on, char off);

private:
    void CreateMesh();
    void CreateNormal();
    void CreateTangent();

private:
    vector<VertexType> vertices;
    CameraBuffer* cameraBuffer;
    MosterLightBuffer* monsterLightBuffer;

    bool Plane_off = true;
    Vector3 size;
};