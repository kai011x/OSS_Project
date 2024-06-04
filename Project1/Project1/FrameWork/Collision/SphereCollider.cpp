#include "Framework.h"

SphereCollider::SphereCollider(float radius, UINT stackCount, UINT sliceCount)
    :radius(radius), stackCount(stackCount), sliceCount(sliceCount)
{
    type = SPHERE;

	float phiStep = XM_PI / stackCount;
	float thetaStep = XM_2PI / sliceCount;

	//Vertices
	for (UINT i = 0; i <= stackCount; i++)
	{
		float phi = i * phiStep;

		for (UINT j = 0; j <= sliceCount; j++)
		{
			float theta = j * thetaStep;

			Vertex vertex;

			vertex.pos.x = sin(phi) * cos(theta) *radius;
			vertex.pos.y = cos(phi) * radius;
			vertex.pos.z = sin(phi) * sin(theta) * radius;

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
	
			indices.push_back((sliceCount + 1) * i + j);//0
			indices.push_back((sliceCount + 1) * (i + 1) + j);//2
		}
	}

	CreateMesh();
}

bool SphereCollider::RayCollision(IN Ray ray, OUT Contact* contact)
{
	UpdateWorld();

	Vector3 P = ray.position;
	Vector3 D = ray.direction;

	Vector3 C = GlobalPos();
	Vector3 A = P - C;

	float b = Vector3::Dot(D, A);
	float c = Vector3::Dot(A, A) - Radius() * Radius();
	
	if (b * b >= c)
	{
		if (contact != nullptr)
		{
			float t = -b - sqrt(b * b - c);
			if (A.length() < Radius()) { t = -b + sqrt(b * b - c); }	// 원내부에 있을떄 접하는거 
			if (t < 0)return false;
			contact->distance = t;
			contact->hitPoint = P + D * t;
		}

		return true;
	}

    return false;
}

bool SphereCollider::BoxCollision(BoxCollider* collider)
{
    return collider->SphereCollision(this);
}

bool SphereCollider::SphereCollision(SphereCollider* collider)
{
	float distance = Vector3::Distance(GlobalPos(), collider->GlobalPos());

    return distance <= Radius() + collider->Radius();
}

bool SphereCollider::CapsuleCollision(CapsuleCollider* collider)
{
    return false;
}
