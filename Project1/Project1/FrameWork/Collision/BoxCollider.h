#pragma once

class BoxCollider : public Collider
{
public:
	struct ObbDesc
	{
		Vector3 position;
		Vector3 axis[3];	// up, right, forward
		Vector3 halfSize;
	};

public:
	BoxCollider(Vector3 size = Vector3(1,1,1));
	~BoxCollider();

	virtual bool RayCollision(IN Ray ray, OUT Contact* contact = nullptr) override;
	virtual bool BoxCollision(BoxCollider* collider) override;
	virtual bool SphereCollision(SphereCollider* collider) override;
	virtual bool CapsuleCollision(CapsuleCollider* collider) override;

	void GetObb(ObbDesc& obbDesc);

private:
	bool IsSeperateAxis(Vector3 D,Vector3 axis, ObbDesc box1, ObbDesc box2);

private:
	Vector3 size;

};
