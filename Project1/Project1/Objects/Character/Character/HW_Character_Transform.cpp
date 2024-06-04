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
	// dir = �о�� ����
//	dir = dir.Normalize();									// ������ ���� ���ͷ� �ٲٱ�
	Vector3 forward = -1 * this->Forward();					// ĳ���� ���� ����
	forward = forward.Normalize();							// ��������� ���� ���ͷ� �����
	float arrange = Vector3::Dot(forward, dir);				// ���� ����� �о� ���� ���� ���� cos�� ���ϱ�
	// arrange =  ������ // abs���ϸ� ���� �������� ����
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