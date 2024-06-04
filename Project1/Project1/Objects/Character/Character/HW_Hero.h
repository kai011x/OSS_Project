#pragma once

class HW_Hero : public HW_Basic_Character
{
private:


public:
	HW_Hero(string file);
	~HW_Hero();

	virtual void Update() override;
	virtual void Render() override;
	virtual void Hit(UINT damage) override;

	virtual void Set_respawn_Pos(Vector3 pos) override { this->Position() = pos; }

private:
	void Move();								// ������ ����
	
private:
	HW_RectCollider* Check_Area(Vector3 pos);  //�浹ó�� ����

private:
	int CurHp = 5;

	HW_Dungeon* dungeon = nullptr;

	short move_Speed = 10;			// �⺻ �ӵ�
	short rot_Speed = 5;			// ĳ���� ȸ�� �ӵ�

	ImVec4 text_Color = { 1,1,1,1 };
	float text_Color_Time = 0.0f;		//�ؽ�Ʈ �� ������ ���� ������
};
