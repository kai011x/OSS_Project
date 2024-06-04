#include "Framework.h"
// 과제 : 쿼드, 큐브, 터레인에 노멀맵핑 적용시키기

Cube::Cube(Vector3 size) : GameObject(L"Shaders/LandScape/TerrainEditor.hlsl"), size(size)
{
    CreateMesh();
	cameraBuffer = new CameraBuffer();
	monsterLightBuffer = new MosterLightBuffer();

}

Cube::~Cube()
{
	delete cameraBuffer;
	delete monsterLightBuffer;
}
void Cube::Render()
{    
	cameraBuffer->data.camera_Pos = CAMERA->GlobalPos();
	cameraBuffer->data.lenght = CAMERA->Get_Eye_Sight();
	cameraBuffer->SetVSBuffer(9);
	monsterLightBuffer->SetPSBuffer(8);
	GameObject::Render();
}

void Cube::InstancingRender(UINT instanceCount)
{
	cameraBuffer->data.camera_Pos = CAMERA->GlobalPos();
	cameraBuffer->data.lenght = CAMERA->Get_Eye_Sight();
	
	for (int i = 0; i < 3; i++)
	{
		monsterLightBuffer->data.monster_Pos[i] = HW_CHARACTER->Get_PackMan_Monsters()[i]->Get_Monster_Buffer_data();
	}

	cameraBuffer->SetVSBuffer(9);
	monsterLightBuffer->SetPSBuffer(8);
	GameObject::InstancingRender(instanceCount);
}

void Cube::Update_En(char on, char off)
{
    if (GetAsyncKeyState(off))
        Plane_off = true;
    if (GetAsyncKeyState(on))
        Plane_off = false;
    
    if (Plane_off)
        Environment::Get()->Set_off();
    else
        Environment::Get()->Set_on();
    
}

void Cube::CreateMesh()
{
    Float3 halfSize;
    halfSize.x = size.x * 0.5f;
    halfSize.y = size.y * 0.5f;
    halfSize.z = size.z * 0.5f;

    // 앞면은 Quad와 같음
	// -- -+ ++ +- 순으로 0,1,2,0,2,3의 인덱스를 가며 tagent는 다른 축으로 +1 normal은 그 반대이다.
	vertices.emplace_back(-halfSize.x, -halfSize.y, -halfSize.z, 0, 1, 0, 0, -1, 1, 0, 0); //  0
	vertices.emplace_back(-halfSize.x, +halfSize.y, -halfSize.z, 0, 0, 0, 0, -1, 1, 0, 0); //  1
	vertices.emplace_back(+halfSize.x, +halfSize.y, -halfSize.z, 1, 0, 0, 0, -1, 1, 0, 0); //  2
	vertices.emplace_back(+halfSize.x, -halfSize.y, -halfSize.z, 1, 1, 0, 0, -1, 1, 0, 0); //  3
	
	// 뒤                                                               
	vertices.emplace_back(+halfSize.x, -halfSize.y, +halfSize.z, 0, 1, 0, 0, +1, -1, 0, 0);  //  4
	vertices.emplace_back(+halfSize.x, +halfSize.y, +halfSize.z, 0, 0, 0, 0, +1, -1, 0, 0);  //  5
	vertices.emplace_back(-halfSize.x, +halfSize.y, +halfSize.z, 1, 0, 0, 0, +1, -1, 0, 0);  //  6
	vertices.emplace_back(-halfSize.x, -halfSize.y, +halfSize.z, 1, 1, 0, 0, +1, -1, 0, 0);  //  7
			
	// 위
	vertices.emplace_back(-halfSize.x, +halfSize.y, -halfSize.z, 0, 1, 0, 1, 0, 1, 0, 0);  //  8
	vertices.emplace_back(-halfSize.x, +halfSize.y, +halfSize.z, 0, 0, 0, 1, 0, 1, 0, 0);  //  9
	vertices.emplace_back(+halfSize.x, +halfSize.y, +halfSize.z, 1, 0, 0, 1, 0, 1, 0, 0);  //  10
	vertices.emplace_back(+halfSize.x, +halfSize.y, -halfSize.z, 1, 1, 0, 1, 0, 1, 0, 0);  //  11

	// 아래
	vertices.emplace_back(-halfSize.x, -halfSize.y, +halfSize.z, 0, 1, 0, -1, 0, 1, 0, 0);  //  12
	vertices.emplace_back(-halfSize.x, -halfSize.y, -halfSize.z, 0, 0, 0, -1, 0, 1, 0, 0);  //  13
	vertices.emplace_back(+halfSize.x, -halfSize.y, -halfSize.z, 1, 0, 0, -1, 0, 1, 0, 0);  //  14
	vertices.emplace_back(+halfSize.x, -halfSize.y, +halfSize.z, 1, 1, 0, -1, 0, 1, 0, 0);  //  15

	// 좌측
	vertices.emplace_back(-halfSize.x, -halfSize.y, +halfSize.z, 0, 1, -1, 0, 0, 0, 0, -1);  //  16
	vertices.emplace_back(-halfSize.x, +halfSize.y, +halfSize.z, 0, 0, -1, 0, 0, 0, 0, -1);  //  17
	vertices.emplace_back(-halfSize.x, +halfSize.y, -halfSize.z, 1, 0, -1, 0, 0, 0, 0, -1);  //  18
	vertices.emplace_back(-halfSize.x, -halfSize.y, -halfSize.z, 1, 1, -1, 0, 0, 0, 0, -1);  //  19

	// 우측
	vertices.emplace_back(+halfSize.x, -halfSize.y, -halfSize.z, 0, 1, +1, 0, 0, 0, 0,+1);  //  20
	vertices.emplace_back(+halfSize.x, +halfSize.y, -halfSize.z, 0, 0, +1, 0, 0, 0, 0,+1);  //  21
	vertices.emplace_back(+halfSize.x, +halfSize.y, +halfSize.z, 1, 0, +1, 0, 0, 0, 0,+1);  //  22
	vertices.emplace_back(+halfSize.x, -halfSize.y, +halfSize.z, 1, 1, +1, 0, 0, 0, 0,+1);  //  23

	//Index Buffer
	indices = { 0,1,2,0,2,3,    // 앞
	            4,5,6,4,6,7,    // 뒤
				8,9,10,8,10,11,	//위
				12,13,14,12,14,15,	//아래
				16,17,18,16,18,19,	// 좌측
				20,21,22,20,22,23	//우측
	};

	CreateTangent();

    mesh = new Mesh(vertices.data(), sizeof(VertexType), vertices.size(), indices.data(), indices.size());
}

void Cube::CreateNormal()
{
}

void Cube::CreateTangent()
{
}
