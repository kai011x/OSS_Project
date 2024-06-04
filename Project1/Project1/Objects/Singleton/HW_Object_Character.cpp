#include "Framework.h"
#include "HW_Object_Character.h"

HW_Object_Character::HW_Object_Character()
{
//	hero = new HW_Hero("Arissa");

//	Add_Drake(3);
//	Add_Epioth(4);
//	Add_Boss();

//	Add_Defence_Epioth(30);
//	Add_Defence_Drake(10);
//	Add_Defence_Boss();

	basic_Character = new HW_Character_Transform();

	// r 담당
	HW_Packman_Monster* monster_r = new HW_Packman_Monster(L"Textures/Monster/Specimen_4.png", 2, 4, { 0,497 }, { 1536,0 }, 6, 1);
	monster_r->Set_Character(basic_Character);
	monsters.push_back(monster_r);
	// g담당
	HW_Packman_Monster* monster_g = new HW_Packman_Monster(L"Textures/Monster/Specimen_2.png", 2, 4, { 0,505 }, { 1280,0 }, 5, 1);
	monster_g->Set_Character(basic_Character);
	monsters.push_back(monster_g);
	// b 담당
	HW_Packman_Monster* monster_b = new HW_Packman_Monster(L"Textures/Monster/Spooky.png", 3, 4, { 4,483 }, { 3423,10 }, 9, 1);
	monster_b->Set_Character(basic_Character);
	monsters.push_back(monster_b);
}
HW_Object_Character::~HW_Object_Character()
{
	delete hero;

	for (pair<string, vector<HW_Basic_Character*>> pair: characters)
	{
		for (HW_Basic_Character* character : pair.second)
			delete character;
	}
	characters.clear();

	delete basic_Character;

	for (HW_Packman_Monster* monster : monsters)
		delete monster;
}

void HW_Object_Character::Update(string key)
{
	if (characters[key].size() == 0) return;

	for (HW_Basic_Character* character : characters[key])
		character->Update();
	
}

void HW_Object_Character::Render(string key)
{
	if (characters[key].size() == 0) return;

	for (HW_Basic_Character* character : characters[key])
		character->Render();
	
}

void HW_Object_Character::GUIRender(string key)
{
	if (characters[key].size() == 0) return;

	for (HW_Basic_Character* character : characters[key])
		character->GUIRender();
}

void HW_Object_Character::Defence_Update(string key)
{
	if (defence_Characters[key].size() == 0) return;

	for (HW_Basic_Character* character : defence_Characters[key])
		character->Update();
}

void HW_Object_Character::Defence_Render(string key)
{
	if (defence_Characters[key].size() == 0) return;

	for (HW_Basic_Character* character : defence_Characters[key])
		character->Render();
}

void HW_Object_Character::Defence_GUIRender(string key)
{
	if (defence_Characters[key].size() == 0) return;

	for (HW_Basic_Character* character : defence_Characters[key])
		character->GUIRender();
}

//void HW_Object_Character::Add_Drake(UINT num)
//{
//	if (characters["Drake"].size() > num) return;
//
//	UINT cur_size = characters["Drake"].size();
//
//	for (UINT i = cur_size; i < num; i++)
//	{
//		HW_Drake* Drake = new HW_Drake();
//		Drake->Get_Character(hero);
//		Drake->Get_Info_Name() = "Drake_" + to_string(i);
//		Drake->GetModel()->Tag() = Drake->Get_Info_Name();
//		Drake->Get_Area(HW_MAP->Get_Dungeon("Dungeon")->Get_Areas()[2]);
//		characters["Drake"].push_back(Drake);
//	}
//}
//
//void HW_Object_Character::Add_Epioth(UINT num)
//{
//	if (characters["Epioth"].size() > num) return;
//
//	UINT cur_size = characters["Epioth"].size();
//
//	for (UINT i = cur_size; i < num; i++)
//	{
//		HW_Epioth* Epioth = new HW_Epioth();
//		Epioth->Get_Character(hero);
//		Epioth->Get_Info_Name() = "Epioth_" + to_string(i);
//		Epioth->GetModel()->Tag() = Epioth->Get_Info_Name();
//		Epioth->Get_Area(HW_MAP->Get_Dungeon("Dungeon")->Get_Areas()[1]);
//		characters["Epioth"].push_back(Epioth);
//	}
//}
//
//void HW_Object_Character::Add_Boss()
//{
//	if (characters["Boss"].size() > 0) return;
//
//	HW_Boss* boss = new HW_Boss();
//	boss->Get_Character(hero);
//	boss->Get_Info_Name() = "Boss";
//	boss->GetModel()->Tag() = boss->Get_Info_Name();
//	boss->Get_Area(HW_MAP->Get_Dungeon("Dungeon")->Get_Areas()[3]);
//	characters["Boss"].push_back(boss);
//	
//}

/*=============================== Defence ======================================*/
//void HW_Object_Character::Add_Defence_Drake(UINT num)
//{
//	if (defence_Characters["Drake"].size() > num) return;
//
//	UINT cur_size = defence_Characters["Drake"].size();
//
//	for (UINT i = cur_size; i < num; i++)
//	{
//		HW_DefenceDrake* Drake = new HW_DefenceDrake();
//		Drake->Set_Target_Tower(HW_TOWER->Get_Commander_Tower());
//		Drake->Set_Defence_Dungeon(HW_MAP->Get_Defence_Dungeon("Defence"));
//		Drake->Get_Info_Name() = "Drake";
//		Drake->GetModel()->Tag() = Drake->Get_Info_Name();
//
//		defence_Characters["Drake"].push_back(Drake);
//	}
//}
//
//void HW_Object_Character::Add_Defence_Epioth(UINT num)
//{
//	if (defence_Characters["Epioth"].size() > num) return;
//
//	UINT cur_size = defence_Characters["Epioth"].size();
//
//	for (UINT i = cur_size; i < num; i++)
//	{
//		HW_DefenceEpioth* Epioth = new HW_DefenceEpioth();
////		Epioth->Get_Character(hero);
////		Epioth->Get_Info_Name() = "Epioth_" + to_string(i);
////		Epioth->GetModel()->Tag() = Epioth->Get_Info_Name();
////		Epioth->Get_Area(HW_MAP->Get_Dungeon("Dungeon")->Get_Areas()[1]);
//		defence_Characters["Epioth"].push_back(Epioth);
//	}
//}
//
//void HW_Object_Character::Add_Defence_Boss()
//{
//	if (defence_Characters["Boss"].size() > 0) return;
//
//	HW_DefenceBoss* boss = new HW_DefenceBoss();
//	boss->Set_Target_Tower(HW_TOWER->Get_Commander_Tower());
//	boss->Set_Defence_Dungeon(HW_MAP->Get_Defence_Dungeon("Defence"));
//	boss->Get_Info_Name() = "Boss";
//	boss->GetModel()->Tag() = boss->Get_Info_Name();
//
//	defence_Characters["Boss"].push_back(boss);
//
//}
