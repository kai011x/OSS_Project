#include "Framework.h"

Material::Material(string Load_file,wstring shader_file, string ID)
{
	buffer = new MaterialBuffer();
	file_manager = new Material_File_Manager(ID,"");
	SetShader(shader_file);

	char path[128];
	GetCurrentDirectoryA(128, path);
	projectPath = path;

	SelectShader();

	file_manager->Load_data(Load_file);
	Update_Value();
	Update_Map();
}

Material::Material()
{
	buffer = new MaterialBuffer();
	file_manager = new Material_File_Manager("None", "");
	char path[128];
	GetCurrentDirectoryA(128, path);

	projectPath = path;

	Update_Value();
	Update_Map();
}

Material::Material(wstring shader_file)
{
	buffer = new MaterialBuffer();
	file_manager = new Material_File_Manager("None", "");
	SetShader(shader_file);

	char path[128];
	GetCurrentDirectoryA(128, path);

	projectPath = path;

	Update_Value();
	Update_Map();
}

Material::~Material()
{
	delete file_manager;
	delete buffer;
}

void Material::Set()
{
	buffer->SetPSBuffer(1);

	if (DMap[0] != nullptr)
		DMap[0]->PSSet(0);

	if (SMap[0] != nullptr)
		SMap[0]->PSSet(1);

	if (NMap[0] != nullptr)
		NMap[0]->PSSet(2);

	for (UINT i = 1; i < 3; i++)
	{
		if (DMap[i] != nullptr)
			DMap[i]->PSSet(10 + i);

		if (SMap[i] != nullptr)
			SMap[i]->PSSet(12 + i);

		if (NMap[i] != nullptr)
			NMap[i]->PSSet(14 + i);
	}

	vertexShader->Set();
	pixelShader->Set();
}

void Material::GUIRender()
{
	if (ImGui::TreeNode(file_manager->Get_File_name().c_str()))
	{
		SelectShader();

		if (ImGui::TreeNode("Value"))
		{
			ImGui::ColorEdit3("Diffuse", (float*)&file_manager->Get_Mat().D, ImGuiColorEditFlags_PickerHueBar);
			ImGui::ColorEdit3("Specular", (float*)&file_manager->Get_Mat().S, ImGuiColorEditFlags_PickerHueBar);
			ImGui::ColorEdit3("ambient", (float*)&file_manager->Get_Mat().A, ImGuiColorEditFlags_PickerHueBar);

			ImGui::SliderFloat("Shininess", &file_manager->Get_Mat().Shiniess, 1.0f, 50.0f);

			ImGui::SliderInt("Select_Map", (int*)&select_Map, 0, 2);
			ImGui::TreePop();
		}

		Make_Texture_Button();
		ImGui::TreePop();
	}

	file_manager->GUIRender();
	Update_Value();
	Update_Map();
}

void Material::Update_Map()
{
	buffer->data.hasDM0 = true;
	buffer->data.hasDM1 = true;
	buffer->data.hasDM2 = true;

	buffer->data.hasSM0 = true;
	buffer->data.hasSM1 = true;
	buffer->data.hasSM2 = true;

	buffer->data.hasNM0 = true;
	buffer->data.hasNM1 = true;
	buffer->data.hasNM2 = true;

	for (int i = 0; i < 3; i++)
	{
		if (file_manager->Get_Mat().DM[i] == L"None"){
			DMap[i] = nullptr;
		}
		else if (DMap[i] == nullptr) {
			DMap[i] = Texture::Add(file_manager->Get_Mat().DM[i]);
		}
		else if (DMap[i]->GetFile() != file_manager->Get_Mat().DM[i]){
			DMap[i] = Texture::Add(file_manager->Get_Mat().DM[i]);
		}

		if (file_manager->Get_Mat().SM[i] == L"None"){
			SMap[i] = nullptr;
		}
		else if (SMap[i] == nullptr){ 
			SMap[i] = Texture::Add(file_manager->Get_Mat().SM[i]);
		}
		else if (SMap[i]->GetFile() != file_manager->Get_Mat().SM[i]){
			SMap[i] = Texture::Add(file_manager->Get_Mat().SM[i]);
		}

		if (file_manager->Get_Mat().NM[i] == L"None"){
			NMap[i] = nullptr;
		}
		else if (NMap[i] == nullptr) {
			NMap[i] = Texture::Add(file_manager->Get_Mat().NM[i]);
		}
		else if (NMap[i]->GetFile() != file_manager->Get_Mat().NM[i]){
			NMap[i] = Texture::Add(file_manager->Get_Mat().NM[i]);
		}
	}

	if (DMap[0] == nullptr) { buffer->data.hasDM0 = 0; }
	if (DMap[1] == nullptr) { buffer->data.hasDM1 = 0; }
	if (DMap[2] == nullptr) { buffer->data.hasDM2 = 0; }

	if (SMap[0] == nullptr) { buffer->data.hasSM0 = 0; }
	if (SMap[1] == nullptr) { buffer->data.hasSM1 = 0; }
	if (SMap[2] == nullptr) { buffer->data.hasSM2 = 0; }

	if (NMap[0] == nullptr) { buffer->data.hasNM0 = 0; }
	if (NMap[1] == nullptr) { buffer->data.hasNM1 = 0; }
	if (NMap[2] == nullptr) { buffer->data.hasNM2 = 0; }

}
void Material::SetDiffuseMap(wstring file, UINT num)
{
	if (file.length() == 0)
	{
		DMap[num] = nullptr;
		file_manager->Get_Mat().DM[num] = L"None";
		return;
	}

	DMap[num] = Texture::Add(file);
	file_manager->Get_Mat().DM[num] = file;

	if (DMap[num] == nullptr) {
		if (num == 0)buffer->data.hasDM0 = false;
		if (num == 1)buffer->data.hasDM1 = false;
		if (num == 2)buffer->data.hasDM2 = false;
	}
	else
	{
		if (num == 0)buffer->data.hasDM0 = true;
		if (num == 1)buffer->data.hasDM1 = true;
		if (num == 2)buffer->data.hasDM2 = true;
	}
}
void Material::SetSpecularMap(wstring file, UINT num)
{
	if (file.length() == 0)
	{
		SMap[num] = nullptr;
		file_manager->Get_Mat().SM[num] = L"None";
		return;
	}

	SMap[num] = Texture::Add(file);
	file_manager->Get_Mat().SM[num] = file;
	if (SMap[num] == nullptr) {
		if (num == 0)buffer->data.hasSM0 = false;
		if (num == 1)buffer->data.hasSM1 = false;
		if (num == 2)buffer->data.hasSM2 = false;
	}
	else
	{
		if (num == 0)buffer->data.hasSM0 = true;
		if (num == 1)buffer->data.hasSM1 = true;
		if (num == 2)buffer->data.hasSM2 = true;
	}
}
void Material::SetNormalMap(wstring file, UINT num)
{
	if (file.length() == 0)
	{
		NMap[num] = nullptr;
		file_manager->Get_Mat().NM[num] = L"None";
		return;
	}

	NMap[num] = Texture::Add(file);
	file_manager->Get_Mat().NM[num] = file;
	if (NMap[num] == nullptr) {
		if (num == 0)buffer->data.hasNM0 = false;
		if (num == 1)buffer->data.hasNM1 = false;
		if (num == 2)buffer->data.hasNM2 = false;
	}
	else
	{
		if (num == 0)buffer->data.hasNM0 = true;
		if (num == 1)buffer->data.hasNM1 = true;
		if (num == 2)buffer->data.hasNM2 = true;
	}
}

void Material::SetShader(wstring file)
{
	vertexShader = Shader::AddVS(file);
	pixelShader = Shader::AddPS(file);

	file_manager->Get_Mat().vertexShader = file;
	file_manager->Get_Mat().pixelShader = file;
}

void Material::SelectShader()
{
	if (ImGui::Button((file_manager->Get_Mat().name + "Shader").c_str()))
	{
		DIALOG->OpenDialog((file_manager->Get_Mat().name + "Shader"), "SelectShader", ".hlsl", ".");
	}
	

	if (DIALOG->Display((file_manager->Get_Mat().name + "Shader").c_str()))
	{
		if (DIALOG->IsOk())
		{
			string file = DIALOG->GetFilePathName();

			char path[128];
			GetCurrentDirectoryA(128, path);

			file = file.substr(strlen(path) + 1, file.length());

			file_manager->Get_Mat().vertexShader = ToWString(file);
			file_manager->Get_Mat().pixelShader = ToWString(file);
		}

		DIALOG->Close();
	}
}

void Material::Make_Texture_Button()
{
	if (ImGui::TreeNode("Textures"))
	{
		ImTextureID texture;
		if (DMap[0] == nullptr)texture = nullptr; else texture = DMap[0]->GetSRV();
		file_manager->SeleceMap("DM", file_manager->DIFFUSE, 0, texture);

		ImGui::SameLine();
		if (SMap[0] == nullptr)texture = nullptr; else texture = SMap[0]->GetSRV();
		file_manager->SeleceMap("SM", file_manager->SPECULAR, 0, texture);

		ImGui::SameLine();
		if (NMap[0] == nullptr)texture = nullptr; else texture = NMap[0]->GetSRV();
		file_manager->SeleceMap("NM", file_manager->NORMAL, 0, texture);

		file_manager->Delete_Button(0);
		/*================================================================================*/
		if (DMap[1] == nullptr)texture = nullptr; else texture = DMap[1]->GetSRV();
		file_manager->SeleceMap("DM", file_manager->DIFFUSE, 1, texture);

		ImGui::SameLine();
		if (SMap[1] == nullptr)texture = nullptr; else texture = SMap[1]->GetSRV();
		file_manager->SeleceMap("SM", file_manager->SPECULAR, 1, texture);

		ImGui::SameLine();
		if (NMap[1] == nullptr)texture = nullptr; else texture = NMap[1]->GetSRV();
		file_manager->SeleceMap("NM", file_manager->NORMAL, 1, texture);

		file_manager->Delete_Button(1);
		/*================================================================================*/
		if (DMap[2] == nullptr)texture = nullptr; else texture = DMap[2]->GetSRV();
		file_manager->SeleceMap("DM", file_manager->DIFFUSE, 2, texture);

		ImGui::SameLine();
		if (SMap[2] == nullptr)texture = nullptr; else texture = SMap[2]->GetSRV();
		file_manager->SeleceMap("SM", file_manager->SPECULAR, 2, texture);

		ImGui::SameLine();
		if (NMap[2] == nullptr)texture = nullptr; else texture = NMap[2]->GetSRV();
		file_manager->SeleceMap("NM", file_manager->NORMAL, 2, texture);
		file_manager->Delete_Button(2);

		ImGui::TreePop();
	}
}
void Material::Update_Value()
{
	buffer->data.diffuse.x = file_manager->Get_Mat().D.x;
	buffer->data.diffuse.y = file_manager->Get_Mat().D.y;
	buffer->data.diffuse.z = file_manager->Get_Mat().D.z;

	buffer->data.specular.x = file_manager->Get_Mat().S.x;
	buffer->data.specular.y = file_manager->Get_Mat().S.y;
	buffer->data.specular.z = file_manager->Get_Mat().S.z;

	buffer->data.ambient.x = file_manager->Get_Mat().A.x;
	buffer->data.ambient.y = file_manager->Get_Mat().A.y;
	buffer->data.ambient.z = file_manager->Get_Mat().A.z;

	buffer->data.shininess = file_manager->Get_Mat().Shiniess;

	if (file_manager->Get_Mat().vertexShader != L"None")
	{
		if (vertexShader->GetFile() != file_manager->Get_Mat().vertexShader)
		{
			if (vertexShader != nullptr)
				vertexShader = nullptr;
			vertexShader = Shader::AddVS(file_manager->Get_Mat().vertexShader);
		}
	}
	if (file_manager->Get_Mat().pixelShader != L"None")
	{
		if (vertexShader->GetFile() != file_manager->Get_Mat().pixelShader)
		{
			if (pixelShader != nullptr)
				pixelShader = nullptr;
			pixelShader = Shader::AddPS(file_manager->Get_Mat().pixelShader);
		}
	}
}