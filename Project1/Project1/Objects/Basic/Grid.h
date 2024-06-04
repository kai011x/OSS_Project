#pragma once

class Grid
{
private:
	const int MAX_VALUE = 100;

public:
	Grid();
	~Grid();

	void Render();

private:
	Material* material;
	VertexBuffer* vertexBuffer;
	MatrixBuffer* worldBuffer;

	vector<VertexColor> vertices;

	UINT width, height;


};
