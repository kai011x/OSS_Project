#include "Framework.h"

ModelObject::ModelObject(string name, Collider::Type type)
	:Model(name)
{
	switch (type)
	{
	case Collider::BOX:
		collider = new BoxCollider();
		break;
	case Collider::SPHERE:
		collider = new SphereCollider();
		break;
	case Collider::CAPSULE:
		collider = new CapsuleCollider();
		break;
	case Collider::NONE:
		break;
	}

	collider->Tag() = name + "Collider";
	collider->SetParent(this);
	collider->Load();
}

ModelObject::~ModelObject()
{
	delete collider;
}

void ModelObject::Update()
{
	Model::Update();
	collider->UpdateWorld();
}

void ModelObject::Render()
{
	if (!Active())return;

	Model::Render();
	collider->Render();
}


void ModelObject::GUIRender()
{
	if (!Active())return;

	Model::GUIRender();
	collider->GUIRender();
}
