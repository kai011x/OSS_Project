#pragma once

struct Ray
{
	Vector3 position;
	Vector3 direction;
};

struct Contact // 충돌시 충돌 반환값
{
	string tag;

	Vector3 hitPoint;
	float distance;	//충돌위치와의 거리
};

class BoxCollider;
class SphereCollider;
class CapsuleCollider;

class Collider : public Transform
{
public:
	enum Type
	{
		BOX = 0, SPHERE, CAPSULE, NONE
	};

public:
	Collider();
	~Collider();

	void Render();

	bool Collision(Collider* collider);

	virtual bool RayCollision(IN Ray ray, OUT Contact* contact = nullptr) = 0;
	virtual bool BoxCollision(BoxCollider* collider) = 0;
	virtual bool SphereCollision(SphereCollider* collider) = 0;
	virtual bool CapsuleCollision(CapsuleCollider* collider) = 0;

	void SetColor(Float4 color) { material->GetData().diffuse = color; }
	void SetColor(float r, float g, float b) { material->GetData().diffuse = Float4(r, g, b, 1.0f); }

	static void SwitchRender() { isCollider_Render = !isCollider_Render; }
protected:
	void CreateMesh();

private:
	Material* material;
	MatrixBuffer* worldBuffer;

protected:
	Mesh* mesh;
	Type type;

	vector<Vertex> vertices;
	vector<UINT> indices;

	static bool isCollider_Render;
};
