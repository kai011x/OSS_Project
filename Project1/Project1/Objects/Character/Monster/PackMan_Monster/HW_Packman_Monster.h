#pragma once

class HW_Packman_Monster : public Transform
{
public:
	HW_Packman_Monster(	wstring file, float width, float height, 
						Float2 left_top_pixel, Float2 right_bottom_pixel, 
						UINT width_clip_num, UINT height_clip_num);
	~HW_Packman_Monster();

	void Update();
	void Render();
	void GUIRender();

	void Set_AStar(AStar* aStar) { this->aStar = aStar; }
	void Set_Character(HW_Character_Transform* character) { this->character = character; }
	void Set_Respawn_Pos(Vector3 pos) { this->respawn_Pos = pos; }

	Float4 Get_Monster_Buffer_data() { return { Position().x, Position().y, Position().z,(float)is_trace }; }
private:
	void Search();		// ĳ���� ��ġ �˻� 1�ʿ� �ѹ� �˻��� ��
	void Move();

private:
	AStar* aStar;
	vector<Vector3> path;
	// ������ ��ġ�θ� �˻�
	Anime_2D* anime;
	HW_Character_Transform* character;

	Vector3 respawn_Pos = { 0,0,0 };

	int is_trace  = 0;		//0�� ���� ���� 1�� ������

	Vector3 velocity;
	Vector3 destPos;
	float search_Time = 0.0f;
	float move_Speed = 7.0f;
	float attack_Range = 2.0f;

};

// �⺻ ��ȹ 1�ʿ� �ѹ� ĳ���Ϳ� �Ÿ��� �˻��ϵ� ���� �� �Ÿ��� 7ĭ�̻� �������ٸ� 
// ������ ��Ҹ� �ٽ� �˻� �ؼ� �ֺ��� ���� �ٴҰ�