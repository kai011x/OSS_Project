#include "Framework.h"
#include "HW_Hero.h"

HW_Hero::HW_Hero(string file)
	:HW_Basic_Character(file)
{

	

	CAMERA->SetTarget(this);
	dungeon = HW_MAP->Get_Dungeon("Dungeon");
}

HW_Hero::~HW_Hero()
{
}

void HW_Hero::Update()
{

	if (text_Color_Time <= 0)
	{
		text_Color_Time = 0;
		text_Color = { 1,1,1,1 };
	}
	else
		text_Color_Time -= DELTA;

	Move();

	
	this->Update_Basis();
}

void HW_Hero::Render()
{
	this->Render_Basis();
}



void HW_Hero::Move()
{
	
	if (KEY_PRESS(ImGuiKey_UpArrow))
	{
		Position() -= this->Forward() * DELTA * move_Speed;
	}
	if (KEY_PRESS(ImGuiKey_DownArrow))
	{
		Position() += this->Forward() * DELTA * move_Speed;
	}
	if (KEY_PRESS(ImGuiKey_LeftArrow))
	{
		Rotation().y -= DELTA * rot_Speed;
	}
	if (KEY_PRESS(ImGuiKey_RightArrow))
	{
		Rotation().y += DELTA * rot_Speed;
	}

}



void HW_Hero::Hit(UINT damage)
{
	CurHp -= damage;
	text_Color = { 1,0,0,1 };
	text_Color_Time = 1.0f;
}



HW_RectCollider* HW_Hero::Check_Area(Vector3 pos)
{
	for (HW_RectCollider* area : dungeon->Get_Areas())
	{
		if (area->Tag() == "Rect0")
			continue;

		if (area->Check_Area(pos))
			return area;
	}

	return nullptr;
}
