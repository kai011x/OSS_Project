#pragma once

class CapsuleCollider : public Collider
{
public:
	CapsuleCollider(float radius = 1.0f, float height = 2.0f, UINT stackCount = 8, UINT sliceCount = 16);
	~CapsuleCollider();

	virtual bool RayCollision(IN Ray ray, OUT Contact* contact = nullptr) override;
	virtual bool BoxCollision(BoxCollider* collider) override;
	virtual bool SphereCollision(SphereCollider* collider) override;
	virtual bool CapsuleCollision(CapsuleCollider* collider) override;

	float Radius() { return radius * max(GlobalScale().x, max(GlobalScale().y, GlobalScale().z)); }
	float Height() { return height * GlobalScale().y; }
private:
	float radius,height;
	UINT stackCount, sliceCount;
};
