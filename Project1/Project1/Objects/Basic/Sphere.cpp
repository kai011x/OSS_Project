#include "Framework.h"

Sphere::Sphere(float radius, UINT sliceCount, UINT stackCount)
	: GameObject(L"Shaders/Light/NormalMapping.hlsl") , radius(radius) , sliceCount(sliceCount), stackCount(stackCount)
{
	Tag() = "Sphere";
	CreateMesh();
}

Sphere::~Sphere()
{

}

void Sphere::Render()
{
	this->Render();
}


void Sphere::CreateMesh()
{

	float phiStep = XM_PI / stackCount;
	float thetaStep = XM_2PI / sliceCount;

	//Vertices
	for (UINT i = 0; i <= stackCount; i++)
	{
		float phi = i * phiStep;

		for (UINT j = 0; j <= sliceCount; j++)
		{
			float theta = j * thetaStep;

			VertexType vertex;

			vertex.normal.x = sin(phi) * cos(theta);
			vertex.normal.y = cos(phi);
			vertex.normal.z = sin(phi) * sin(theta);

			vertex.pos = Vector3(vertex.normal) * radius;

			vertex.uv.x = (float)j / sliceCount;
			vertex.uv.y = (float)i / stackCount;

			vertices.push_back(vertex);
		}
	}

	//Indices
	for (UINT i = 0; i < stackCount; i++)
	{
		for (UINT j = 0; j < sliceCount; j++)
		{
			indices.push_back((sliceCount + 1) * i + j);//0
			indices.push_back((sliceCount + 1) * i + j + 1);//1
			indices.push_back((sliceCount + 1) * (i + 1) + j);//2

			indices.push_back((sliceCount + 1) * (i + 1) + j);//2
			indices.push_back((sliceCount + 1) * i + j + 1);//1
			indices.push_back((sliceCount + 1) * (i + 1) + j + 1);//1
		}
	}

	CreateTangent();

	mesh = new Mesh(vertices.data(), sizeof(VertexType), vertices.size(),
		indices.data(), indices.size());
}

void Sphere::CreateTangent()
{
	for (UINT i = 0; i < indices.size() / 3; i++)
	{
		UINT index0 = indices[i * 3 + 0];
		UINT index1 = indices[i * 3 + 1];
		UINT index2 = indices[i * 3 + 2];

		VertexType vertex0 = vertices[index0];
		VertexType vertex1 = vertices[index1];
		VertexType vertex2 = vertices[index2];

		Vector3 p0 = vertex0.pos;
		Vector3 p1 = vertex1.pos;
		Vector3 p2 = vertex2.pos;

		Float2 uv0 = vertex0.uv;
		Float2 uv1 = vertex1.uv;
		Float2 uv2 = vertex2.uv;

		Vector3 e0 = p1 - p0;
		Vector3 e1 = p2 - p0;

		float u0 = uv1.x - uv0.x;
		float v0 = uv1.y - uv0.y;
		float u1 = uv2.x - uv0.x;
		float v1 = uv2.y - uv0.y;

		float d = (1.0f) / (u0 * v1 - v0 * u1);

		Vector3 tangent = d * (e0 * v1 - e1 * v0);

		vertices[index0].tangent += tangent;
		vertices[index1].tangent += tangent;
		vertices[index2].tangent += tangent;
	}

	// tangent 보정단계
	for (VertexType& vertex : vertices)
	{
		Vector3 t = vertex.tangent;
		Vector3 n = vertex.normal;

		vertex.tangent = (t - n * Vector3::Dot(n, t)).Normalize();
	}
}