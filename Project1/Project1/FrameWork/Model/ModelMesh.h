#pragma once

class ModelMesh
{
public:
	ModelMesh(string name);
	~ModelMesh();

	void Render();
	void InstancingRender(UINT indstanceCount);

	void CreateMesh(void* vertexData, UINT vertexCount, void* indexData, UINT indexCount);

	void SetMaterial(Material* material) { this->material = material; }
private:
	string name;

	Material* material;
	Mesh* mesh;

	UINT vertexCount;
	UINT indexCount;

	ModelVertex* vertices;
	UINT* indices;

};

