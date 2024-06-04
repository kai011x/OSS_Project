#include "Framework.h"
#include "Quad.h"

Quad::Quad(Float2 size) : GameObject(L"Shaders/PacManShaders/PackMan_Shader/PackManShader_Texture.hlsl"), size(size)
{
	CreateMesh();
	cameraBuffer = new CameraBuffer();
	monsterLightBuffer = new MosterLightBuffer();

	Load();
}

Quad::~Quad()
{
	delete cameraBuffer;

}


void Quad::Render()
{
	cameraBuffer->data.camera_Pos = CAMERA->GlobalPos();
	cameraBuffer->data.lenght = CAMERA->Get_Eye_Sight();
	for (int i = 0; i < 3; i++)
	{
		monsterLightBuffer->data.monster_Pos[i] = HW_CHARACTER->Get_PackMan_Monsters()[i]->Get_Monster_Buffer_data();
	}

	cameraBuffer->SetPSBuffer(9);
	monsterLightBuffer->SetPSBuffer(8);

	GameObject::Render();
}

void Quad::CreateMesh()
{
	Float2 halfSize;
	halfSize.x = size.x * 0.5f;
	halfSize.y = size.y * 0.5f;

	// -- -+ ++ +- 순으로 0,1,2,0,2,3의 인덱스를 가며 tagent는 다른 축으로 +1 normal은 그 반대이다.
	VertexType vertex;
	vertex.pos = { -halfSize.x , -halfSize.y , 0.0f };
	vertex.uv = { 0,1 };
	vertex.normal = { 0,0,-1 };
	vertex.tangent = { 1,0,0 };

	vertices.push_back(vertex);

	vertex.pos = { -halfSize.x , +halfSize.y , 0.0f };
	vertex.uv = { 0,0 };

	vertices.push_back(vertex);

	vertex.pos = { +halfSize.x , +halfSize.y , 0.0f };
	vertex.uv = { 1,0 };

	vertices.push_back(vertex);

	vertex.pos = { +halfSize.x , -halfSize.y , 0.0f };
	vertex.uv = { 1,1 };

	vertices.push_back(vertex);

	indices = { 0,1,2,0,2,3 };
	mesh = new Mesh(vertices.data(), sizeof(VertexType), vertices.size(), indices.data(), indices.size());

}
