#include "Framework.h"

Grid::Grid() : width(MAX_VALUE) , height(MAX_VALUE)
{
	material = new Material(L"Shaders/Basic/Grid.hlsl");

	// Axis X
	vertices.emplace_back(-MAX_VALUE, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	vertices.emplace_back(+MAX_VALUE, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);

	// Axis Y
	vertices.emplace_back(0.0f, -MAX_VALUE, 0.0f, 0.0f, 1.0f, 0.0f);
	vertices.emplace_back(0.0f, +MAX_VALUE, 0.0f, 0.0f, 1.0f, 0.0f);

	// Axis Z
	vertices.emplace_back(0.0f, 0.0f, -MAX_VALUE, 0.0f, 0.0f, 1.0f);
	vertices.emplace_back(0.0f, 0.0f, +MAX_VALUE, 0.0f, 0.0f, 1.0f);

	int halfW = width / 2;
	int halfH = height / 2;
	for (int z = -halfH; z <= halfH; z++)
	{
		if (z == 0)continue;

		vertices.emplace_back(-halfH, 0, z, 0.5f, 0.5f, 0.5f);
		vertices.emplace_back(+halfH, 0, z, 0.5f, 0.5f, 0.5f);
	}

	for (int x = -halfW; x <= halfW; x++)
	{
		if (x == 0)continue;

		vertices.emplace_back(x, 0, -halfW, 0.5f, 0.5f, 0.5f);
		vertices.emplace_back(x, 0, +halfW, 0.5f, 0.5f, 0.5f);
	}

	vertexBuffer = new VertexBuffer(vertices.data(), sizeof(VertexColor), vertices.size());

	worldBuffer = new MatrixBuffer();
}

Grid::~Grid()
{
	delete material;
	delete vertexBuffer;
	delete worldBuffer;
}

void Grid::Render()
{
	worldBuffer->SetVSBuffer(0);
	vertexBuffer->IASet(D3D_PRIMITIVE_TOPOLOGY_LINELIST);

	material->Set();
	DC->Draw(vertices.size(), 0);
}
