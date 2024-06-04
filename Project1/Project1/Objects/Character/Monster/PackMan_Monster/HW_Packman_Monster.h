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
	void Search();		// 캐릭터 위치 검색 1초에 한번 검색할 것
	void Move();

private:
	AStar* aStar;
	vector<Vector3> path;
	// 죽음은 위치로만 검색
	Anime_2D* anime;
	HW_Character_Transform* character;

	Vector3 respawn_Pos = { 0,0,0 };

	int is_trace  = 0;		//0은 추적 안함 1은 추적중

	Vector3 velocity;
	Vector3 destPos;
	float search_Time = 0.0f;
	float move_Speed = 7.0f;
	float attack_Range = 2.0f;

};

// 기본 계획 1초에 한번 캐릭터와 거리를 검색하되 만약 그 거리가 7칸이상 떨어졌다면 
// 랜덤한 장소를 다시 검색 해서 주변을 돌아 다닐것