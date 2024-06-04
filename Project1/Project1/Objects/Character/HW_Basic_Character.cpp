#include "Framework.h"
#include "HW_Basic_Character.h"

HW_Basic_Character::HW_Basic_Character(string file)
{
	Tag() = file;

	collider = new SphereCollider(100.0f);
	collider->Position().y = 90.0f;


	Set_Tags(file);
}

HW_Basic_Character::~HW_Basic_Character()
{
	delete collider;
}

void HW_Basic_Character::Update_Basis()
{
	this->UpdateWorld();

	collider->UpdateWorld();
}

void HW_Basic_Character::Render_Basis()
{
	if(Show_Collider)collider->Render();
}




void HW_Basic_Character::Set_Tags(string name)
{
	collider->Tag() = name + "_Colldier";

}