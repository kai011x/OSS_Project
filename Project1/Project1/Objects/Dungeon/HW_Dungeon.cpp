#include "Framework.h"

HW_Dungeon::HW_Dungeon()
{
	dungeon = new Model("Dungeon");
	CreateDungeon();
}

HW_Dungeon::~HW_Dungeon()
{
	delete dungeon;

	for (HW_RectCollider* colldier : areas)
		delete colldier;
}

void HW_Dungeon::Update()
{
	dungeon->Update();

	for (HW_RectCollider* colldier : areas)
		colldier->Update();
}

void HW_Dungeon::Render()
{
	dungeon->Render();

	for (HW_RectCollider* colldier : areas)
		colldier->Render();
}
void HW_Dungeon::GUIRender()
{
	dungeon->GUIRender();

	for (HW_RectCollider* colldier : areas)
		colldier->GUIRender();
}

void HW_Dungeon::CreateDungeon()
{
	// 1. 벽설정 ->rect 하나 만들어서 중점, 가로길이, 세로길이 받아서 colldier하나 만들기
	// 2. 몬스터 지형 설정 -> 자신과 다른 지형에 있다면 쫒아가지 않게 만들예정
	// 위를 위해 필요한 정보 -> 전체 rect하나 만들어서 해당 지형 밖으로 나가려하면 ㅌㅌ하게 만들기
	// 작은 rect 몇개 만들어서 특정 지형 1,2,3,ex로 나뉘어서 자신은 1인데 주인공은 2면 ㅌㅌ하게 하는 설정
	// 리스폰, 정찰terget을 잡을때 자신의 지형이 아니면 다시 설정하게 만들기


	for (UINT i = 0; i < 7; i++)
	{
		HW_RectCollider* colldier = new HW_RectCollider("Rect" + to_string(i));
		areas.push_back(colldier);
	}
}