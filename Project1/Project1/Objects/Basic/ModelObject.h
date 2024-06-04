#pragma once

class ModelObject : public Model
{
public:
	ModelObject(string name, Collider::Type type = Collider::BOX);
	~ModelObject();

	void Update();
	void Render();
	void GUIRender();

	Collider* GetCollider() { return collider; }

private:
	Collider* collider;

};
