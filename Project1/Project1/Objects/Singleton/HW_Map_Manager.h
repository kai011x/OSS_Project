#pragma once

class HW_Map_Manager : public Singleton<HW_Map_Manager>
{
public:
	HW_Map_Manager();
	~HW_Map_Manager();


	HW_Dungeon* Get_Dungeon(string key) { return maps[key]; }
	HW_Pacman_Map* Get_PackMap_Map() { return packMan_Map; }
private:
	map<string, HW_Dungeon*> maps;
	HW_Pacman_Map* packMan_Map;
};
