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
	bool Check_Area(Vector3 pos, float size_x = 0, float size_z = 0);	// �ش���ġ�� ���� Rect���� �ִ��� �ƴ��� Ȯ���ϱ�

	// ���Ͱ� �и����� �ϴµ� ��� ���⿡ �ִ��� Ȯ���ϴ� ���� ���Ͱ� ���� ������ 0,0,0�� ������ �о ������ ������
	Vector3 Get_Push_Dir(Vector3 pos , float size_x = 0, float size_z = 0);
	Vector3 Get_Pull_Dir(Vector3 pos, float size_x = 0, float size_z = 0);
	Vector3 Get_Random_Pos();	// ���� ������ �������� ���ϳ��� �������� �Լ�
private:
	Material* material;
	Mesh* mesh;

	vector<Vertex> vertices;
	vector<UINT> indices;
	MatrixBuffer* worldBuffer;

	UINT width;
	UINT height;
};

