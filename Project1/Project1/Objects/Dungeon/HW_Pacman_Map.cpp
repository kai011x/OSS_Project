#include "Framework.h"
#include "HW_Pacman_Map.h"

HW_Pacman_Map::HW_Pacman_Map()
{
	terrain = new Quad({100,100});
	terrain->Tag() = "Terrain";
	terrain->Getmaterial()->SetDiffuseMap(L"TextData/fieldstone_DM.png");
	terrain->Getmaterial()->SetShader(L"Shaders/PacManShaders/PackMan_Shader/PackManShader_Texture.hlsl");

	terrain2 = new Quad({ 100,100 });
	terrain2->Tag() = "Terrain2";
	terrain2->Getmaterial()->SetDiffuseMap(L"TextData/fieldstone_DM.png");
	terrain2->Getmaterial()->SetShader(L"Shaders/PacManShaders/PackMan_Shader/PackManShader_Texture.hlsl");
	terrain2->Load();

	cube = new Cube({ 1,1,1 });
	cube->Getmaterial()->SetDiffuseMap(L"Textures/Landscape/Floor.png");
	cube->Getmaterial()->SetShader(L"Shaders/PacManShaders/HW_Instancing_Light.hlsl");
	Create_Walls();

	aStar = new AStar();
	aStar->CreateMiddleNode(terrain);
	AStarUpdate();

	coin = new Model("Coin");
	for (Material* material : coin->Get_Reader()->GetMaterial())
		material->SetDiffuseMap(L"Textures/Coin/yellow.png");
	coin->Get_Reader()->SetShader(L"Shaders/Instancing/ModelInstancing.hlsl");
	Create_Coin();

	for (HW_RectCollider* rect : walls)
		rect->Update();
	for (HW_RectCollider* rect : areas)
		rect->Update();

	miniMap = new Quad({ 2,2 });
	miniMap->Getmaterial()->SetDiffuseMap(L"Textures/Coin/White.png");
	miniMap->Getmaterial()->SetShader(L"Shaders/Instancing/Instancing.hlsl");
	miniMap->Getmaterial()->GetData().diffuse.w = 0.1f;
	Create_MiniMap_basic();
//	miniMap->Position() = { WIN_WIDTH - 150, WIN_HEIGHT - 150 };	// ¹Ì´Ï¸Ê À§Ä¡
//	miniMap->Load();

	coin_mini_Map = new Quad({ 3,3 });
	coin_mini_Map->Getmaterial()->SetDiffuseMap(L"Textures/Coin/yellow.png");
	coin_mini_Map->Getmaterial()->SetShader(L"Shaders/Instancing/Instancing.hlsl");
	coin_mini_Map->Getmaterial()->GetData().diffuse.w = 0.5f;
	Create_Coin_MiniMap();

	mini_Map_character = new Quad({ 5,5 });
	mini_Map_character->Tag() = "MiniMap_Character";
	mini_Map_character->Getmaterial()->SetDiffuseMap(L"Textures/Coin/purple.png");
//	coin_mini_Map->Getmaterial()->SetShader(L"Shaders/Instancing/Instancing.hlsl");
	mini_Map_character->Getmaterial()->GetData().diffuse.w = 0.5f;
	mini_Map_character->Rotation().x = 0;
}
 
HW_Pacman_Map::~HW_Pacman_Map()
{
	delete terrain;
	delete terrain2;
	delete cube;

	delete instanceBuffer;
	delete instance_CoinBuffer;
	delete instance_MiniMapBuffer;
	delete instance_coin_MiniMapBuffer;
	
	for (HW_RectCollider* rect : walls)
		delete rect;
	for (HW_RectCollider* rect : areas)
		delete rect;

	delete aStar;
	delete coin;

	delete miniMap;
	delete coin_mini_Map;
	delete mini_Map_character;
}

void HW_Pacman_Map::Update()
{
	terrain->UpdateWorld();
	terrain2->UpdateWorld();

	mini_Map_character->Position() = { 2 * character->Position().x + WIN_WIDTH - 250, 
										2 * character->Position().z + WIN_HEIGHT - 250, 0};

	mini_Map_character->UpdateWorld();

	UpdateTransforms_Coin();
	Push_Hero();
}

void HW_Pacman_Map::Render()
{
	terrain->Render();
	terrain2->Render();

	instanceBuffer->IASet(1);
	cube->InstancingRender(instanceData.size());

	instance_CoinBuffer->IASet(1);
	coin->InstancingRender(drawCount);

	aStar->Render();
	for (HW_RectCollider* rect : walls)
		rect->Render();
	for (HW_RectCollider* rect : areas)
		rect->Render();
}

void HW_Pacman_Map::GUIRender()
{
	if (ImGui::TreeNode("PackMan_Map"))
	{
		terrain->GUIRender();
		terrain2->GUIRender();
		for (HW_RectCollider* rect : walls)
			rect->GUIRender();
		for (HW_RectCollider* rect : areas)
			rect->GUIRender();

		ImGui::TreePop();
	}

	mini_Map_character->GUIRender();
}

void HW_Pacman_Map::InfoRender()
{
	string text = "Coin : " + to_string(cur_Coin_Num) + " / " + to_string(max_Coin_Num);
	ImGui::Text(text.c_str());
}

void HW_Pacman_Map::MiniMap()
{
	instance_MiniMapBuffer->IASet(1);
	miniMap->InstancingRender(instance_MiniMapData.size());

	UpdateTransforms_Coin();
	instance_coin_MiniMapBuffer->IASet(1);
	coin_mini_Map->InstancingRender(260);

	mini_Map_character->Render();
}

void HW_Pacman_Map::AStarUpdate()
{
	int i = 0;
	for (HW_RectCollider* rect : walls)
	{
		for (Node* node : aStar->Get_Nodes())
		{
			if (rect->Check_Area(node->Position()))
			{
				node->Set_Obstacle();
			}
		}
	}
}

HW_RectCollider* HW_Pacman_Map::Get_hit_Wall(Vector3 pos)
{
	for (HW_RectCollider* collider : walls)
	{
		if (collider->Check_Area(pos,-0.5f,-0.5f))
			return collider;
	}

	return nullptr;
}

void HW_Pacman_Map::Create_Walls()
{
	for (UINT i = 0; i < 30; i++)
	{
		HW_RectCollider* rect = new HW_RectCollider("Wall_" + to_string(i));
		rect->SetParent(this);
		walls.push_back(rect);
	}

	for (UINT i = 0; i < 1; i++)
	{
		HW_RectCollider* rect = new HW_RectCollider("Area_" + to_string(i));
		rect->SetParent(this);
		areas.push_back(rect);
	}

	for (HW_RectCollider* rect : walls)
	{
		Matrix transform;

		Vector3 position = rect->GlobalPos();
		Vector3 scale = rect->GlobalScale();
//		Vector3 rotation = rect->Rotation();

		Matrix S = XMMatrixScaling(scale.x, scale.y, scale.z);

		transform = XMMatrixTranslation(position.x, position.y, position.z);
		transform = XMMatrixTranspose(transform);
		transform = transform * S;

		instanceData.push_back(transform);
	}
	instanceBuffer = new VertexBuffer(instanceData.data(), sizeof(Matrix), instanceData.size());

}

void HW_Pacman_Map::Create_Coin()
{
	instance_CoinBuffer = new VertexBuffer(instance_CoinDatas, sizeof(InstanceData), 400);
	int i = 0;
	for (Node* node : aStar->Get_Nodes())
	{
		if (!node->IsObstacle())
		{
			Transform* transform = new Transform();
			transform->Tag() = "Coin_" + to_string(i);
			transform->Position() = node->GlobalPos();
			transform->Scale() = { 0.02f,0.02f,0.02f };
			coin_Transforms.push_back(transform);
			i++;
		}
	}

	max_Coin_Num = i;
	cur_Coin_Num = max_Coin_Num;
}

void HW_Pacman_Map::Create_MiniMap_basic()
{
	Float2 Minimap_Basic_Pos = { WIN_WIDTH - 250,WIN_HEIGHT - 250 };

	for (HW_RectCollider* rect : walls)
	{
		Matrix transform;
		Vector3 position = rect->GlobalPos() * 2;
		Vector3 scale = rect->GlobalScale();

		Matrix S = XMMatrixScaling(scale.x, scale.z, scale.y);

		transform = XMMatrixTranslation(position.x + Minimap_Basic_Pos.x, position.z + Minimap_Basic_Pos.y, 0);
		transform = XMMatrixTranspose(transform);
		transform = transform * S;

		instance_MiniMapData.push_back(transform);
	}
	for (HW_RectCollider* rect : areas)
	{
		Matrix transform;
		Vector3 position = rect->GlobalPos() * 2;
		Vector3 scale = rect->GlobalScale();

		Matrix S = XMMatrixScaling(scale.x, scale.z, scale.y);

		transform = XMMatrixTranslation(position.x+ Minimap_Basic_Pos.x, position.z + Minimap_Basic_Pos.y, 0);
		transform = XMMatrixTranspose(transform);
		transform = transform * S;

		instance_MiniMapData.push_back(transform);
	}

	instance_MiniMapBuffer = new VertexBuffer(instance_MiniMapData.data(), sizeof(Matrix), instance_MiniMapData.size());
}

void HW_Pacman_Map::Create_Coin_MiniMap()
{
	instance_coin_MiniMapBuffer = new VertexBuffer(instance_coin_MiniMapDatas, sizeof(InstanceData), 300);
}


void HW_Pacman_Map::Push_Hero()
{
	if (character == nullptr)return;
	Vector3 hero_position = character->GlobalPos();

	if(!areas[0]->Check_Area(hero_position,1,1))
		character->Push(areas[0]->Get_Pull_Dir(hero_position,1,1));
}

void HW_Pacman_Map::UpdateTransforms_Coin()
{
	Float2 Minimap_Basic_Pos = { WIN_WIDTH - 250,WIN_HEIGHT - 250 };
	drawCount = 0;
	Vector3 character_pos = HW_CHARACTER->Get_Basic_Character()->Position();

	for (UINT i = 0; i < coin_Transforms.size(); i++)
	{
		if (coin_Transforms[i]->Active())
		{
			float distance = Distance2D(character_pos, coin_Transforms[i]->Position());
			if (distance < 5.0f)
			{
				coin_Transforms[i]->SetActive(false);
				cur_Coin_Num--;
				continue;
			}

			coin_Transforms[i]->Rotation().y += 2*DELTA;
			coin_Transforms[i]->Position().y += 2.0f;
			coin_Transforms[i]->UpdateWorld();
			instance_CoinDatas[drawCount].world = XMMatrixTranspose(coin_Transforms[i]->GetWorld());
			instance_CoinDatas[drawCount].index = i;

			Matrix transform;
			Vector3 position = coin_Transforms[i]->Position()*2;

			transform = XMMatrixTranslation(position.x + Minimap_Basic_Pos.x, position.z + Minimap_Basic_Pos.y, 0);
			transform = XMMatrixTranspose(transform);

			instance_coin_MiniMapDatas[i].world = transform;
			instance_coin_MiniMapDatas[i].index = i;

			drawCount++;
		}
		else
		{
			if (instance_coin_MiniMapDatas[i].index != -1)
			{
				Matrix transform;
				Vector3 position = { 500,500,0 };

				transform = XMMatrixTranslation(position.x + Minimap_Basic_Pos.x, position.z + Minimap_Basic_Pos.y, 0);
				transform = XMMatrixTranspose(transform);

				instance_coin_MiniMapDatas[i].world = transform;
				instance_coin_MiniMapDatas[i].index = -1;
			}
		}
	}
	instance_coin_MiniMapBuffer->Update(instance_coin_MiniMapDatas, 260);
	instance_CoinBuffer->Update(instance_CoinDatas, drawCount);
}

