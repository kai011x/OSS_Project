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
	// 1. ������ ->rect �ϳ� ���� ����, ���α���, ���α��� �޾Ƽ� colldier�ϳ� �����
	// 2. ���� ���� ���� -> �ڽŰ� �ٸ� ������ �ִٸ� �i�ư��� �ʰ� ���鿹��
	// ���� ���� �ʿ��� ���� -> ��ü rect�ϳ� ���� �ش� ���� ������ �������ϸ� �����ϰ� �����
	// ���� rect � ���� Ư�� ���� 1,2,3,ex�� ����� �ڽ��� 1�ε� ���ΰ��� 2�� �����ϰ� �ϴ� ����
	// ������, ����terget�� ������ �ڽ��� ������ �ƴϸ� �ٽ� �����ϰ� �����


	for (UINT i = 0; i < 7; i++)
	{
		HW_RectCollider* colldier = new HW_RectCollider("Rect" + to_string(i));
		areas.push_back(colldier);
	}
}