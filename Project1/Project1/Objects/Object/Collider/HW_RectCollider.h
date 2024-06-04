#pragma once

class HW_RectCollider : public Transform
{
public:
	HW_RectCollider(string tag ,UINT width = 1, UINT height = 1);
	~HW_RectCollider();

	void Update();
	void Render();
	void GUIRender();

	void SetColor(Float4 color) { material->GetData().diffuse = color; }
	void SetColor(float r, float g, float b) { material->GetData().diffuse = Float4(r, g, b, 1.0f); }

	Float2 GetSize() { return Float2(width * Scale().x, height * Scale().z); }
	bool Check_Area(Vector3 pos, float size_x = 0, float size_z = 0);	// 해당위치가 지금 Rect위에 있는지 아닌지 확인하기

	// 몬스터가 밀리려고 하는데 어디 방향에 있는지 확인하는 과정 몬스터가 위에 없으면 0,0,0을 있으면 밀어낼 방향을 가져옴
	Vector3 Get_Push_Dir(Vector3 pos , float size_x = 0, float size_z = 0);
	Vector3 Get_Pull_Dir(Vector3 pos, float size_x = 0, float size_z = 0);
	Vector3 Get_Random_Pos();	// 지금 영역중 무작위의 점하나를 가져오는 함수
private:
	Material* material;
	Mesh* mesh;

	vector<Vertex> vertices;
	vector<UINT> indices;
	MatrixBuffer* worldBuffer;

	UINT width;
	UINT height;
};

