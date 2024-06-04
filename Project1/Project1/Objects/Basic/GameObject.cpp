#include "Framework.h"
#include "GameObject.h"

GameObject::GameObject()
{
	material = new Material();
	worldBuffer = new MatrixBuffer();
}

GameObject::GameObject(string Load_File, wstring shaderFile, string ID)
{
	material = new Material(Load_File, shaderFile, ID);
	worldBuffer = new MatrixBuffer();
}

GameObject::GameObject(wstring shaderFile)
{
	material = new Material(shaderFile);
	worldBuffer = new MatrixBuffer();
}

GameObject::~GameObject()
{
	delete worldBuffer;

	delete material;
	delete mesh;
}

void GameObject::Render()
{
	if (!Active()) return;

	worldBuffer->Set(world);
	worldBuffer->SetVSBuffer(0);

	mesh->IASet();
	material->Set();

	DC->DrawIndexed(indices.size(), 0, 0);
}

void GameObject::InstancingRender(UINT instanceCount)
{
	if (!Active()) return;

	worldBuffer->Set(world);
	worldBuffer->SetVSBuffer(0);

	mesh->IASet();
	material->Set();

	DC->DrawIndexedInstanced(indices.size(), instanceCount, 0, 0, 0);
}