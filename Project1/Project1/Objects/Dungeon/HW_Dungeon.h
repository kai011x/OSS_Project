#pragma once

class HW_Dungeon
{
public:
	HW_Dungeon();
	~HW_Dungeon();

	void Update();
	void Render();
	void GUIRender();

	vector<HW_RectCollider*> Get_Areas(){return areas;}
private:
	void CreateDungeon();
private:
	Model* dungeon;
	
	// 지역들 0번지역은 해당 맵 전체이며 그이후 지역은 지역내에서 나뉘어진 영역으로 만들 예정
	vector<HW_RectCollider*> areas;
};
