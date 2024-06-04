#include "Framework.h"

Model::Model(string name) : name(name)
{
	Tag() = name;

	reader = new ModelReader(name);
	reader->SetShader(L"Shaders/Light/NormalMapping.hlsl");

	worldBuffer = new MatrixBuffer();

	for (Material* material : reader->GetMaterial())
		material->Get_Save_File_Manager()->Create_Load();
	
	this->Load();
}

Model::~Model()
{
	delete reader;
	delete worldBuffer;
}

void Model::Update()
{
	this->UpdateWorld();
}


void Model::Render()
{
	worldBuffer->Set(world);
	worldBuffer->SetVSBuffer(0);

	reader->Render();
}
void Model::InstancingRender(UINT instanceCount)
{
	worldBuffer->Set(world);
	worldBuffer->SetVSBuffer(0);

	reader->InstancingRender(instanceCount);
}

void Model::GUIRender()
{
	Transform::GUIRender();
	reader->GUIRender();
}



void Model::Set_Color(Float4 color)
{
	for (Material* material : reader->GetMaterial())
		material->GetData().diffuse = color;
}