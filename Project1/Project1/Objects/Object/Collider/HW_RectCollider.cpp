#include "Framework.h"

HW_RectCollider::HW_RectCollider(string tag,UINT width, UINT height)
	:width(width), height(height)
{
	Tag() = tag;

	material = new Material(L"Shaders/Basic/Collider.hlsl");
	worldBuffer = new MatrixBuffer();

	Float2 halfSize = { (float)width / 2, (float)height / 2 };
	
	vertices.emplace_back(Float3(-halfSize.x, 0, -halfSize.y));	//0
	vertices.emplace_back(Float3(-halfSize.x, 0, +halfSize.y));	//1
	vertices.emplace_back(Float3(+halfSize.x, 0, +halfSize.y));	//2
	vertices.emplace_back(Float3(+halfSize.x, 0, -halfSize.y));	//3

	indices = { 0,1,1,2,2,3,3,0 };

	mesh = new Mesh(vertices.data(), sizeof(Vertex), vertices.size(), indices.data(), indices.size());

	SetColor(0, 1, 0);
	Load();
}

HW_RectCollider::~HW_RectCollider()
{
	delete material;
	delete mesh;
	delete worldBuffer;
}

void HW_RectCollider::Update()
{
	this->UpdateWorld();
}

void HW_RectCollider::Render()
{
	if (!Active())return;

	worldBuffer->Set(world);
	worldBuffer->SetVSBuffer(0);

	mesh->IASet(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	material->Set();

	DC->DrawIndexed(indices.size(), 0, 0);
}

void HW_RectCollider::GUIRender()
{
	Transform::GUIRender();
}

bool HW_RectCollider::Check_Area(Vector3 pos, float size_x, float size_z)
{
	// size_x, size_z 는 보정 수치
	this->UpdateWorld();

	Vector3 dir = pos - this->GlobalPos();	// 지금 이곳에서 확인하려는 목표까지의 방향
	
	Vector3 forward_Dir = this->Forward();	// (0,0,1)
	Vector3 right_Dir = this->Right();		// (1,0,0)
	float dot_z_axis = Vector3::Dot(forward_Dir, dir);
	float dot_x_axis = Vector3::Dot(right_Dir, dir);

	float globalScale_Collider_x = (float)width/2 * this->GlobalScale().x - size_x;
	float globalScale_Collider_z = (float)height/2 * this->GlobalScale().z - size_z;

	if (abs(dot_x_axis) < abs(globalScale_Collider_x) && abs(dot_z_axis) < abs(globalScale_Collider_z))
	{
		// 3D 라서 추가되는 조건문
		float dot_y_axis = Vector3::Dot(this->Up(), dir);
		if(abs(dot_y_axis) < 0.01f)
			return true;
	}
	return false;
}

Vector3 HW_RectCollider::Get_Push_Dir(Vector3 pos, float size_x, float size_z)
{
	this->UpdateWorld();

	if (!Check_Area(pos, size_x, size_z))return { 0,0,0 };

	// 우리가 보는 colldier의 최종 사이즈
	float globalScale_Collider_x = ((float)width / 2 * this->GlobalScale().x) - size_x;
	float globalScale_Collider_z = ((float)height / 2 * this->GlobalScale().z) - size_z;
	
	Vector3 pos_1 = (this->Forward() * globalScale_Collider_z + this->Right() * globalScale_Collider_x).Normalize();	// right + forward
	Vector3 pos_3 =( this->Forward() * globalScale_Collider_z - this->Right() * globalScale_Collider_x).Normalize();	// left + forward

	Vector3 center_to_Pos = (pos - this->GlobalPos()).Normalize(); //center -> pos

	Vector3 cross_P1_CP = Vector3::Cross(center_to_Pos, pos_1);
	Vector3 cross_P3_CP = Vector3::Cross(center_to_Pos, pos_3);

	float cross_adjudge = Vector3::Dot(cross_P1_CP, cross_P3_CP);

	if (cross_adjudge < 0)
	{
		// 전방이거나 후방이거나
		float cos_angle = Vector3::Dot(center_to_Pos, this->Forward());
		if (cos_angle > 0)
			return this->Forward();
		else
			return -1 * this->Forward();
	}
	else
	{
		// 좌측이거나 우측이거나
		float cos_angle = Vector3::Dot(center_to_Pos, this->Right());
		if (cos_angle > 0)
			return this->Right();
		else
			return -1 * this->Right();
	}


	return this->Forward();
}

Vector3 HW_RectCollider::Get_Pull_Dir(Vector3 pos, float size_x, float size_z)
{
	this->UpdateWorld();

	if (Check_Area(pos, size_x, size_z))return { 0,0,0 };	// 안에 있으면 ㅌㅌ

	// 우리가 보는 colldier의 최종 사이즈
	float globalScale_Collider_x = ((float)width / 2 * this->GlobalScale().x) - size_x;
	float globalScale_Collider_z = ((float)height / 2 * this->GlobalScale().z) - size_z;

	Vector3 pos_1 = (this->Forward() * globalScale_Collider_z + this->Right() * globalScale_Collider_x).Normalize();	// right + forward
	Vector3 pos_3 = (this->Forward() * globalScale_Collider_z - this->Right() * globalScale_Collider_x).Normalize();	// left + forward

	Vector3 center_to_Pos = (pos - this->GlobalPos()).Normalize(); //center -> pos

	Vector3 cross_P1_CP = Vector3::Cross(center_to_Pos, pos_1);
	Vector3 cross_P3_CP = Vector3::Cross(center_to_Pos, pos_3);

	float cross_adjudge = Vector3::Dot(cross_P1_CP, cross_P3_CP);

	if (cross_adjudge < -0.01f)
	{
		// 전방이거나 후방이거나
		float cos_angle = Vector3::Dot(center_to_Pos, this->Forward());
		if (cos_angle > 0)
			return -1*this->Forward();
		else
			return this->Forward();
	}
	else if(cross_adjudge > 0.01f)
	{
		// 좌측이거나 우측이거나
		float cos_angle = Vector3::Dot(center_to_Pos, this->Right());
		if (cos_angle > 0)
			return -1*this->Right();
		else
			return this->Right();
	}
	else
	{
		return -2 * center_to_Pos;
	}

	// 최종 방향만 반대 방향으로
	return this->Forward();
}

Vector3 HW_RectCollider::Get_Random_Pos()
{
	this->UpdateWorld();

	float globalScale_Collider_x = (float)width / 2 * this->GlobalScale().x;
	float globalScale_Collider_z = (float)height / 2 * this->GlobalScale().z;

	float lenght_x = Random(-globalScale_Collider_x, globalScale_Collider_x);
	float lenght_z = Random(-globalScale_Collider_z, globalScale_Collider_z);

	Vector3 randomPos = this->GlobalPos();
	randomPos += this->Forward() * lenght_z + this->Right() * lenght_x;
	return randomPos;
}


