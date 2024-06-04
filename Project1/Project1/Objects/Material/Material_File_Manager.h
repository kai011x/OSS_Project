#pragma once

class Material_File_Manager
{
public:
	enum  MapType
	{
		DIFFUSE, SPECULAR, NORMAL
	};
private:
	struct AppleMat
	{
		string name = "Material";	// 저장 파일 이름
		Float3 D = { 1.0f,1.0f,1.0f };
		Float3 S = { 1.0f,1.0f,1.0f };
		Float3 A = { 1.0f,1.0f,1.0f };
		float Shiniess = 24.0f;

		wstring DM[3] = { L"None",L"None" ,L"None" };
		wstring SM[3] = { L"None",L"None" ,L"None" };
		wstring NM[3] = { L"None",L"None" ,L"None" };

		wstring height_map = L"None";
		wstring alpha_map = L"None";

		wstring vertexShader = L"None";
		wstring pixelShader = L"None";

	};

public:
	// 저장 파일 이름과 파일 경로를 입력 받을 것
	Material_File_Manager(string name , string line);
	~Material_File_Manager();

	void Save();
	void Save_data(string file);
	void Load();
	void Load_data(string file);

	void Create_Load();

	void SeleceMap(string name, MapType type, UINT num, ImTextureID text);
	void UnSelectMap(MapType type , UINT num);
	void Delete_Button(UINT num);

	void GUIRender();

	AppleMat& Get_Mat() { return data; }
	string& Get_File_name() { return data.name; }
	string& Get_File_line() { return file_line; }

	bool height_alpha_save = false;
private:
	string file_line;	// 파일 경로
	MapType type;
	AppleMat data;
};

