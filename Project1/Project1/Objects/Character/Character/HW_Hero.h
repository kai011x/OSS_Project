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
	void Move();								// 움직임 관련
	
private:
	HW_RectCollider* Check_Area(Vector3 pos);  //충돌처리 관련

private:
	int CurHp = 5;

	HW_Dungeon* dungeon = nullptr;

	short move_Speed = 10;			// 기본 속도
	short rot_Speed = 5;			// 캐릭터 회전 속도

	ImVec4 text_Color = { 1,1,1,1 };
	float text_Color_Time = 0.0f;		//텍스트 색 조정을 위한 보정값
};
