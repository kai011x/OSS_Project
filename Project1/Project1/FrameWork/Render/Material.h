#pragma once

class Material
{
public:
	class MaterialBuffer : public ConstantBuffer
	{
	public:
		struct Data
		{
			Float4 diffuse ={1.0f,1.0f,1.0f,1.0f};
			Float4 specular = { 1.0f,1.0f,1.0f,1.0f };
			Float4 ambient = { 1.0f,1.0f,1.0f,1.0f };

			float shininess =24.0f;

			int hasDM0 = 0;
			int hasDM1 = 0;
			int hasDM2 = 0;

			int hasSM0 = 0;
			int hasSM1 = 0;
			int hasSM2 = 0;

			int hasNM0 = 0;
			int hasNM1 = 0;
			int hasNM2 = 0;

			int make_mode = 1;
			int padding_mat;

		}data;

	public:
		MaterialBuffer(): ConstantBuffer(&data, sizeof(Data)){}
	};

public:
	Material(string Load_file, wstring shader_file, string ID = "None");
	Material();
	Material(wstring shader_file);
	~Material();

	void Set();
	void SetShader(wstring file);

	void GUIRender();
	void Update_Map();
	void Update_Value();

public:
	void SetDiffuseMap(wstring file,UINT num = 0);
	void SetSpecularMap(wstring file, UINT num = 0);
	void SetNormalMap(wstring file, UINT num = 0);
	void SetName(string name) { file_manager->Get_Mat().name = name; }

	MaterialBuffer::Data& GetData() { return buffer->data; }

	Texture*& GetHeightMap() { return hightMap; }
	Texture*& GetAlphaMap() { return alphaMap; }

	wstring GetHeight_map_name() { return file_manager->Get_Mat().height_map; }
	wstring GetAlpha_map_name() { return file_manager->Get_Mat().alpha_map; }
	bool& Get_height_alpha_save() { return file_manager->height_alpha_save; }
	
	Material_File_Manager* Get_Save_File_Manager() {return file_manager;}
	int select_Map = 0;	//�ٲ� �� ���� 2���� DM������ 2��° DM�ٲٴ� �� / alpha�ٲٴµ� ���

	Texture*& GetDMap(UINT num) { return DMap[num]; }
private:
	void SelectShader();
	void Make_Texture_Button();

	VertexShader* vertexShader = nullptr;
	PixelShader* pixelShader = nullptr;

	Texture* DMap[3];
	Texture* SMap[3];
	Texture* NMap[3];
	Texture* hightMap;
	Texture* alphaMap;

	MaterialBuffer* buffer;
	Material_File_Manager* file_manager;

	string projectPath;
};