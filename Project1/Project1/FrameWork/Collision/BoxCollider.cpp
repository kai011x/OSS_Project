#include "Framework.h"

BoxCollider::BoxCollider(Vector3 size):size(size)
{
	type = BOX;

	Vector3 halfSize = size * 0.5f;

	vertices.emplace_back(-halfSize.x, +halfSize.y, -halfSize.z);
	vertices.emplace_back(+halfSize.x, +halfSize.y, -halfSize.z);
	vertices.emplace_back(-halfSize.x, -halfSize.y, -halfSize.z);
	vertices.emplace_back(+halfSize.x, -halfSize.y, -halfSize.z);

	vertices.emplace_back(-halfSize.x, +halfSize.y, +halfSize.z);
	vertices.emplace_back(+halfSize.x, +halfSize.y, +halfSize.z);
	vertices.emplace_back(-halfSize.x, -halfSize.y, +halfSize.z);
	vertices.emplace_back(+halfSize.x, -halfSize.y, +halfSize.z);

	indices = {
		0,1,1,3,3,2,2,0,
		4,5,5,7,7,6,6,4,
		0,4,1,5,2,6,3,7
	};

	CreateMesh();
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::GetObb(ObbDesc& obbDesc)
{
	obbDesc.position = GlobalPos();

	obbDesc.axis[0] = Right();
	obbDesc.axis[1] = Up();
	obbDesc.axis[2] = Forward();

	obbDesc.halfSize = size * 0.5f * GlobalScale();
}

bool BoxCollider::RayCollision(IN Ray ray, OUT Contact* contact)
{
	UpdateWorld();

	float tMin = 0.0f;
	float tMax = FLT_MAX;

	ObbDesc box;
	GetObb(box);

	Vector3 min = box.halfSize * -1.0f;
	Vector3 max = box.halfSize;

	Vector3 delta = box.position - ray.position;
	Vector3 D = ray.direction.Normalize();

	for (UINT i = 0; i < 3; i++)
	{
		Vector3 axis = box.axis[i];
		float e = Vector3::Dot(axis, delta);
		float f = Vector3::Dot(D, axis);
		if (abs(f) < FLT_EPSILON)
		{
			if (min[i] > e || max[i] < e)return false;
		}
		else
		{
			float t1 = (e + min[i]) / f;
			float t2 = (e + max[i]) / f;
			
			if (t1 > t2)swap(t1, t2);
			if (t2 < tMax)tMax = t2;
			if (t1 > tMin)tMin = t1;
			if (tMin > tMax)return false;
		}
	}

	if (contact != nullptr)
	{
		contact->distance = tMin;
		contact->hitPoint = ray.position + ray.direction * tMin;
	}

	return true;
}

bool BoxCollider::BoxCollision(BoxCollider* collider)
{
	ObbDesc box1, box2;
	GetObb(box1);	// 내꺼
	collider->GetObb(box2); // 니꺼

	Vector3 D = box2.position - box1.position;

	for (UINT i = 0; i < 3; i++)
	{
		if (IsSeperateAxis(D, box1.axis[i], box1, box2))return false;
		if (IsSeperateAxis(D, box2.axis[i], box1, box2))return false;
	}
	// 회전안하면 여기서 끝
	for (UINT i = 0; i < 3; i++)
	{
		for (UINT j = 0; j < 3; j++)
		{
			if (box1.axis[i] == box2.axis[j])return true;
		}
	}

	for (UINT i = 0; i < 3; i++)
	{
		for (UINT j = 0; j < 3; j++)
		{
			Vector3 cross = Vector3::Cross(box1.axis[i], box2.axis[j]);
			if (IsSeperateAxis(D, cross, box1, box2))return false;
		}
	}

	return true;
}

bool BoxCollider::SphereCollision(SphereCollider* collider)
{
	ObbDesc box;
	GetObb(box);

	Vector3 pos = box.position;

	for (UINT i = 0; i < 3; i++)
	{
		float lenght = Vector3::Dot(box.axis[i], collider->GlobalPos() - box.position);
		float mult = (lenght < 0.0f) ? -1.0f : 1.0f;
		
		lenght = min(abs(lenght), box.halfSize[i]);
		pos += box.axis[i] * lenght * mult;
	}

	float distance = Vector3::Distance(collider->GlobalPos(), pos);

	return distance <= collider->Radius();
}

bool BoxCollider::CapsuleCollision(CapsuleCollider* collider)
{
	return collider->BoxCollision(this);
}

bool BoxCollider::IsSeperateAxis(Vector3 D, Vector3 axis, ObbDesc box1, ObbDesc box2)
{
	float distance = abs(Vector3::Dot(D, axis));

	float a = 0.0f;
	float b = 0.0f;

	for (UINT i = 0; i < 3; i++)
	{
		a += abs(Vector3::Dot(box1.axis[i] * box1.halfSize[i], axis));
		b += abs(Vector3::Dot(box2.axis[i] * box2.halfSize[i], axis));
	}

	return distance > a + b;
}