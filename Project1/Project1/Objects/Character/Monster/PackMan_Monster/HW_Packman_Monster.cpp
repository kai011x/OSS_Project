#include "Framework.h"

HW_Packman_Monster::HW_Packman_Monster(wstring file, float width, float height, Float2 left_top_pixel, Float2 right_bottom_pixel, UINT width_clip_num, UINT height_clip_num)
{
	anime = new Anime_2D(file, width, height, left_top_pixel, right_bottom_pixel, width_clip_num, height_clip_num);
}

HW_Packman_Monster::~HW_Packman_Monster()
{
	delete anime;
}

void HW_Packman_Monster::Update()
{
	Position().y = 2.0f;
	Search();
	Move();

	anime->Position() = this->Position();
	anime->Scale() = this->Scale();
	this->Rotation().y = CAMERA->Rotation().y;
	anime->Rotation() = this->Rotation();

	anime->Update();
}

void HW_Packman_Monster::Render()
{
	anime->Render();
}

//void HW_Packman_Monster::GUIRender()
//{
//	ImGui::SliderFloat3("dest", (float*)&destPos,0,100);
//	ImGui::SliderFloat3("pos", (float*)&Position(),0,100);
//
//}

void HW_Packman_Monster::Search()
{
	if (search_Time < 1.0f)
	{
		search_Time += DELTA;
		return;
	}
	else
	{
		search_Time = 0;
	}

	HW_MAP->Get_PackMap_Map()->AStarUpdate();

	path.clear();
	destPos = character->Position();
	int start = aStar->FindCloseNode(Position());
	int end = aStar->FindCloseNode(character->Position());
	aStar->GetPath(start, end, path);

	is_trace = 1;

	if (path.size() > 7)
	{
		Vector3 random_Pos;
		random_Pos.x = Random(-10.0f, 10.0f);
		random_Pos.z = Random(-10.0f, 10.0f);

		path.clear();
		start = aStar->FindCloseNode(Position());
		end = aStar->FindCloseNode(respawn_Pos + random_Pos);
		aStar->GetPath(start, end, path);

		is_trace = 0;
	}
}

void HW_Packman_Monster::Move()
{
	if (path.empty())
	{
		return;
	}

	Vector3 dest = path.back();

	Vector3 direction = dest - Position();
	direction.y = 0.0f;

	if (direction.length() < 0.1f)
		path.pop_back();

	velocity = direction.Normalize();

	Position() += velocity * move_Speed * DELTA;
}


