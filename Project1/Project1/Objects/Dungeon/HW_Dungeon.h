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
	
	// ������ 0�������� �ش� �� ��ü�̸� ������ ������ ���������� �������� �������� ���� ����
	vector<HW_RectCollider*> areas;
};
