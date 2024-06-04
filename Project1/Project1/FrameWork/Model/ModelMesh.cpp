#include "Framework.h"

ModelMesh::ModelMesh(string name)
	:name(name)
{

}

ModelMesh::~ModelMesh()
{
	delete mesh;
	delete[] vertices;
	delete[] indices;
}

void ModelMesh::Render()
{
	mesh->IASet();
	material->Set();

	DC->DrawIndexed(indexCount, 0, 0);
}

void ModelMesh::InstancingRender(UINT indstanceCount)
{
	mesh->IASet();
	material->Set();

	DC->DrawIndexedInstanced(indexCount,indstanceCount, 0, 0, 0);
}

void ModelMesh::CreateMesh(void* vertexData, UINT vertexCount, void* indexData, UINT indexCount)
{
	mesh = new Mesh(vertexData, sizeof(ModelVertex), vertexCount, indexData, indexCount);

	this->vertexCount = vertexCount;
	this->indexCount = indexCount;
	vertices = (ModelVertex*)vertexData;
	indices = (UINT*)indexData;
}
