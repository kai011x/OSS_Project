#include "Framework.h"

HW_Map_Manager::HW_Map_Manager()
{


	packMan_Map = new HW_Pacman_Map();

}

HW_Map_Manager::~HW_Map_Manager()
{
	for (pair<string, HW_Dungeon*> map : maps)
		delete map.second;


	delete packMan_Map;
}

