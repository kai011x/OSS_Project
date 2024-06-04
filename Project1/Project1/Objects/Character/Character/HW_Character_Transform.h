#pragma once

class HW_Character_Transform : public Transform
{
	// ��¥ �ſ�ſ�ſ�ſ�ſ�ſ� �⺻���� transform
public:
	HW_Character_Transform();
	~HW_Character_Transform();

	void Update();
	void Render();
	void GUIRender();

	void Push(Vector3 dir);

	BoxCollider* Get_Collider() { return collider; }
private:
	void Move();
private:
	float move_Speed = 10.0f;
	float rot_Speed = 5.0f;
	BoxCollider* collider;	// �⺻ collider�̰� ������ �Ⱥ��ϵ�
};

