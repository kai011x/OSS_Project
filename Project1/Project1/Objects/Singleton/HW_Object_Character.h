#pragma once

class HW_Object_Character : public Singleton<HW_Object_Character>
{
public:
	HW_Object_Character();
	~HW_Object_Character();

	void Update(string key);
	void Render(string key);
	void GUIRender(string key);


	void Defence_Update(string key);
	void Defence_Render(string key);
	void Defence_GUIRender(string key);

	void Add_Drake(UINT num);
	void Add_Epioth(UINT num);
	void Add_Boss();

	void Add_Defence_Drake(UINT num);
	void Add_Defence_Epioth(UINT num);
	void Add_Defence_Boss();

	HW_Basic_Character*& Get_Character(string key, UINT num) { return characters[key][num]; }
	vector<HW_Basic_Character*>& Get_Characters(string key) {return characters[key];}
	vector<HW_Basic_Character*>& Get_Defence_Characters(string key) { return defence_Characters[key]; }
	HW_Character_Transform*& Get_Basic_Character() { return basic_Character; }
	vector<HW_Packman_Monster*>& Get_PackMan_Monsters() { return monsters; }

	unordered_map<string, vector<HW_Basic_Character*>> Get_Character_map() {return characters;}
	unordered_map<string, vector<HW_Basic_Character*>> Get_Defence_Character_map() { return defence_Characters; }

	HW_Hero* Get_Hero() {return hero;}
private:
	unordered_map<string, vector<HW_Basic_Character*>> characters;
	unordered_map<string, vector<HW_Basic_Character*>> defence_Characters;
	HW_Hero* hero;

	HW_Character_Transform* basic_Character;
	vector<HW_Packman_Monster*> monsters;

};

