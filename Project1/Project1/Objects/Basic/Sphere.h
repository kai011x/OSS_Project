#pragma once

class Sphere : public GameObject
{
private:
	typedef VertexUVNormalTangent VertexType;

public:
	Sphere(float radius = 1.0f, UINT sliceCount = 20 , UINT stackCount = 10);
	~Sphere();

	void Render();
	void CreateTangent();

private:
	void CreateMesh();

public:
	vector<VertexType> vertices;

	UINT sliceCount;
	UINT stackCount;

	float radius;
};
