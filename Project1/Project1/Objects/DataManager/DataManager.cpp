#include "Framework.h"

DataManager::DataManager()
{
    LoadMonsterData();
}

DataManager::~DataManager()
{

}

MonsterData DataManager::GetMonsterData(UINT key)
{
    if (monsterDatas.count(key) == 0)return MonsterData();

    return monsterDatas[key];
}

void DataManager::LoadMonsterData()
{
    ifstream loadStream("TextData/Tables/Monster_Table.csv", ios::in);

    bool isFirst_Line = true;
    string str; 
    while (true)
    {
        loadStream >> str;

        if (str.empty())return;

        if (isFirst_Line)
        {
            isFirst_Line = false;
            continue;
        }

        // ���⼭ �ȵǸ� �޸������� csv���� ���ڵ� ANSI�� �ٲ���
        vector<string> temp = SplitString(str, ",");

        MonsterData data;
        data.key = stoi(temp[0]);
        data.name = temp[1];
        data.Attack = stof(temp[2]);
        data.hp = stof(temp[3]);
        data.move_Speed = stof(temp[4]);
     //   data.rot_Speed = stof(temp[5]);
 
        monsterDatas[data.key] = data;

        str = "";
    }

   
}
