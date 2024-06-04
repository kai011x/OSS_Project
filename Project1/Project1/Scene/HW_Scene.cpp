#include "Framework.h"
#include "HW_Scene.h"

HW_Scene::HW_Scene()
{
	HW_CHARACTER->Get_Basic_Character()->Position() = { 20.0f,0.0f,10.0f };
	HW_MAP->Get_PackMap_Map()->Set_Hero(HW_CHARACTER->Get_Basic_Character());

	HW_CHARACTER->Get_PackMan_Monsters()[0]->Set_AStar(HW_MAP->Get_PackMap_Map()->Get_AStar());
	HW_CHARACTER->Get_PackMan_Monsters()[1]->Set_AStar(HW_MAP->Get_PackMap_Map()->Get_AStar());
	HW_CHARACTER->Get_PackMan_Monsters()[2]->Set_AStar(HW_MAP->Get_PackMap_Map()->Get_AStar());
	HW_CHARACTER->Get_PackMan_Monsters()[0]->Set_Respawn_Pos({ 20,2,70 });
	HW_CHARACTER->Get_PackMan_Monsters()[0]->Position() = { 20,2,70 };

	HW_CHARACTER->Get_PackMan_Monsters()[1]->Set_Respawn_Pos({ 70,2,70 });
	HW_CHARACTER->Get_PackMan_Monsters()[1]->Position() = { 70,2,70 };

	HW_CHARACTER->Get_PackMan_Monsters()[2]->Set_Respawn_Pos({ 70,2,20 });
	HW_CHARACTER->Get_PackMan_Monsters()[2]->Position() = { 70,2,20 };

	anime_r = new Anime_2D(L"Textures/Monster/Specimen_4.png", 400, 800, { 0,497 }, { 1536,0 }, 6, 1);
	anime_r->Position() = { CENTER_X, CENTER_Y - 200 };
	anime_r->GetPivotS().y = 250.0f;

	anime_g = new Anime_2D(L"Textures/Monster/Specimen_2.png", 400, 800, { 0,505 }, { 1280,0 }, 5, 1);
	anime_g->Position() = { CENTER_X, CENTER_Y - 200 };
	anime_g->GetPivotS().y = 250.0f;

	anime_b = new Anime_2D(L"Textures/Monster/Spooky.png", 700, 800, { 5,1371 }, { 3647,923 }, 9, 1);
	anime_b->Position() = { CENTER_X, CENTER_Y - 200 };

	Win_anime = new Anime_2D(L"Textures/Monster/Spooky.png", 800, 800, { 5,917 }, { 3855,489 }, 9, 1);
	Win_anime->Position() = { CENTER_X, CENTER_Y - 200 };

	you_Win = new Anime_2D(L"Textures/youWin.png", 300, 300, { 0,300 }, { 300,0 },1, 1);
	you_Win->Position() = { CENTER_X - 200, CENTER_Y + 250 };


	you_Die = new Anime_2D(L"Textures/youDie.png", 300, 300, { 0,300 }, { 300,0 }, 1, 1);
	you_Die->Position() = { CENTER_X + 200, CENTER_Y + 200 };
	you_Win->Update();
	you_Die->Update();
}

HW_Scene::~HW_Scene()
{
	delete anime_r;
	delete anime_g;
	delete anime_b;
	delete Win_anime;

	delete you_Die;
	delete you_Win;

}

void HW_Scene::Update()
{
	cur_coin_num = HW_MAP->Get_PackMap_Map()->Get_Coin_Num();

	if (cur_coin_num <= 0)
	{
		Win_anime->Update();
		return;
	}

	if (hp <= 0) 
	{
		anime_b->Update();
		return;
	}

	if (hit)
	{
		anime_r->Update();
		anime_g->Update();
		anime_b->Update();

		if (hit_Time > 0.001f)
		{
			anime_r->Scale() *= 1.1f;
			anime_g->Scale() *= 1.1f;
			scale_stack++;
			hit_Time -= 0.001f;
		}
		else
		{
			hit_Time += DELTA;
		}

		if (scale_stack > 100)
		{
			hp--;
			HW_CHARACTER->Get_Basic_Character()->Position() = { 20,0,20 };
			HW_CHARACTER->Get_PackMan_Monsters()[0]->Position() = { 20,2,70 };
			HW_CHARACTER->Get_PackMan_Monsters()[1]->Position() = { 70,2,70 };
			HW_CHARACTER->Get_PackMan_Monsters()[2]->Position() = { 70,2,20 };

			hit = false;
			scale_stack = 0;
			anime_r->Scale() = { 1,1,1 };
			anime_g->Scale() = { 1,1,1 };
			hit_Time = 0;
		}
		return;
	}


	HW_CHARACTER->Get_Basic_Character()->Update();
	HW_MAP->Get_PackMap_Map()->Update();
	for (int i = 0; i < 3; i++)
	{
		HW_CHARACTER->Get_PackMan_Monsters()[i]->Update();

		float distance = Distance2D(HW_CHARACTER->Get_Basic_Character()->Position(),
			HW_CHARACTER->Get_PackMan_Monsters()[i]->Position());

		if (distance < 4)
		{
			hit = true;
			anime_num = i;
		}
	}
}

void HW_Scene::PreRender()
{
}

void HW_Scene::Render()
{
	HW_CHARACTER->Get_Basic_Character()->Render();
	HW_MAP->Get_PackMap_Map()->Render();
	for (int i = 0; i < 3; i++)
	{
		HW_CHARACTER->Get_PackMan_Monsters()[i]->Render();
	}
}

void HW_Scene::PostRender()
{
	HW_MAP->Get_PackMap_Map()->MiniMap();

	if (cur_coin_num <= 0)
	{
		Win_anime->Render();
		you_Win->Render();
		return;
	}

	if (hp <= 0)
	{
		anime_b->Render();
		you_Die->Render();
		return;
	}

	if (hit)
	{
		switch (anime_num)
		{
		case 0:
			anime_r->Render();
			break;
		case 1:
			anime_g->Render();
			break;
		case 2:
			anime_b->Render();
			break;

		}
	}
}

void HW_Scene::GUIRender()
{
	/*HW_CHARACTER->Get_Basic_Character()->GUIRender();*/
	/*HW_MAP->Get_PackMap_Map()->GUIRender();*/

}

void HW_Scene::InfoRender()
{
	ImGui::Text(("HP : " + to_string(hp)).c_str());
	HW_MAP->Get_PackMap_Map()->InfoRender();
}

void HW_Scene::UpgradeButton()
{
	if (ImGui::Button("hp_reduce"))
	{
		hp = -1;
		HW_MAP->Get_PackMap_Map()->Get_Coin_Num() = 10;
	}
	if (ImGui::Button("Clear"))
	{
		hp = 5;
		HW_MAP->Get_PackMap_Map()->Get_Coin_Num() = 0;
	}

}