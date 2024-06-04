#pragma once

class HW_Pacman_Map : public Transform
{
public:
	HW_Pacman_Map();
	~HW_Pacman_Map();

	void Update();
	void Render();
	void GUIRender();
	void InfoRender();
	void MiniMap();

	vector<HW_RectCollider*>& Get_Walls() { return walls; }
	vector<HW_RectCollider*>& Get_Areas() { return areas; }
	int& Get_Coin_Num() { return cur_Coin_Num; }

	void Set_Hero(class HW_Character_Transform* character) { this->character = character; }
	AStar*& Get_AStar() { return aStar; }

	void AStarUpdate();

	HW_RectCollider* Get_hit_Wall(Vector3 pos);	
private:
	void Create_Walls();
	void Create_Coin();
	void Create_MiniMap_basic();
	void Create_Coin_MiniMap();

	void Push_Hero();
	void UpdateTransforms_Coin();

private:
	Quad* terrain;
	Quad* terrain2;
	vector<HW_RectCollider*> walls;
	vector<HW_RectCollider*> areas;

	Cube* cube;
	vector<Matrix> instanceData;
	VertexBuffer* instanceBuffer;
	// 큐브 그리기는 instancing으로 할것

	AStar* aStar;
	HW_Character_Transform* character = nullptr;

	Model* coin;
	vector<Transform*> coin_Transforms;
	InstanceData instance_CoinDatas[400];
	VertexBuffer* instance_CoinBuffer;
	int drawCount = 0;

	int max_Coin_Num = 0;
	int cur_Coin_Num = 0;

	Quad* miniMap;	// 베이스
	vector<Matrix> instance_MiniMapData;
	VertexBuffer* instance_MiniMapBuffer;

	Quad* coin_mini_Map;

	InstanceData instance_coin_MiniMapDatas[260];
	VertexBuffer* instance_coin_MiniMapBuffer;

	Quad* mini_Map_character;

};



