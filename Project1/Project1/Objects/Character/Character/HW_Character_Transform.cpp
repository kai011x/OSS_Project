#include "Framework.h"

HW_Character_Transform::HW_Character_Transform()
{
	collider = new BoxCollider({1,2,2});
	collider->SetParent(this);

	CAMERA->SetTarget(this);
}

HW_Character_Transform::~HW_Character_Transform()
{
	delete collider;
}

void HW_Character_Transform::Update()
{
	Move();

	Transform::UpdateWorld();
	collider->UpdateWorld();
}

void HW_Character_Transform::Render()
{
	collider->Render();
}

void HW_Character_Transform::GUIRender()
{
	Transform::GUIRender();
	collider->GUIRender();
}

void HW_Character_Transform::Push(Vector3 dir)
{
	// dir = 밀어내는 방향
//	dir = dir.Normalize();									// 방향을 단위 벡터로 바꾸기
	Vector3 forward = -1 * this->Forward();					// 캐릭터 진행 방향
	forward = forward.Normalize();							// 진행방향을 단위 벡터로 만들기
	float arrange = Vector3::Dot(forward, dir);				// 진행 방향과 밀어 내는 방향 사이 cos각 구하기
	// arrange =  조정값 // abs안하면 같은 방향으로 날림
	this->Position() += dir * move_Speed * DELTA * abs(arrange);
}

void HW_Character_Transform::Move()
{
	if (KEY_PRESS(ImGuiKey_UpArrow))
	{
		Vector3 next_pos = Position() - this->Forward() - 0.1f;

		HW_RectCollider* rect = HW_MAP->Get_PackMap_Map()->Get_hit_Wall(next_pos);

		if(rect == nullptr)
			Position() -= this->Forward() * DELTA * move_Speed;
		else
		{
			Position() -= this->Forward() * DELTA * move_Speed;
			Push(rect->Get_Push_Dir(next_pos, -0.5f, -0.5f));
		}

	}
	if (KEY_PRESS(ImGuiKey_DownArrow))
	{
		Vector3 next_pos = Position() + this->Forward() - 0.1f;

		HW_RectCollider* rect = HW_MAP->Get_PackMap_Map()->Get_hit_Wall(next_pos);

		if (rect == nullptr)
			Position() += this->Forward() * DELTA * move_Speed;
		else
		{
			Position() += this->Forward() * DELTA * move_Speed;
			Push(rect->Get_Push_Dir(next_pos,-0.5f,-0.5f));
		}
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