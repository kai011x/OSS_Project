#pragma once

class SphereCollider : public Collider
{
public:
	SphereCollider(float radius = 1.0f, UINT stackCount = 8, UINT sliceCount = 16);

	virtual bool RayCollision(IN Ray ray, OUT Contact* contact = nullptr) override;
	virtual bool BoxCollision(BoxCollider* collider) override;
	virtual bool SphereCollision(SphereCollider* collider) override;
	virtual bool CapsuleCollision(CapsuleCollider* collider) override;

	float Radius() { return radius * max(GlobalScale().x ,max(GlobalScale().y, GlobalScale().z)); }
private:
	float radius;
	UINT stackCount, sliceCount;

};
