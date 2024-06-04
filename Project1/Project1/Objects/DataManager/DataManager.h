#pragma once

struct MonsterData
{
	UINT key;
	string name;

	float Attack;
	float hp;
	
	float move_Speed;
	float rot_Speed;
};


class DataManager : public Singleton<DataManager>
{
public:
	DataManager();
	~DataManager();

	MonsterData GetMonsterData(UINT key);

private:
	void LoadMonsterData();

private:
	unordered_map<UINT, MonsterData> monsterDatas;


};

