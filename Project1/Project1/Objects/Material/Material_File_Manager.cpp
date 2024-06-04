#include "Framework.h"
#include "Material_File_Manager.h"

Material_File_Manager::Material_File_Manager(string name, string line)
{
	data.name = name;
	file_line = line;
}

Material_File_Manager::~Material_File_Manager()
{
}

void Material_File_Manager::Save()
{
	if (ImGui::Button(("Save__" + data.name).c_str(), ImVec2({ 50.0f,20.0f })))
	{
		if (file_line.empty())
			file_line = "TextData/Materials/" + data.name + ".mat";

		data.height_map = ToWString(file_line) + L"Height.png";
		data.alpha_map = ToWString(file_line) + L"Alpha.png";
		height_alpha_save = true;
		Save_data(file_line);
	}

	ImGui::SameLine();

	if (ImGui::Button(("SaveAs__" + data.name).c_str(), ImVec2({ 50.0f,20.0f })))
	{
		DIALOG->OpenDialog(data.name + "SaveMaterial", "SaveMaterial",
			".mat", ".");
	}

	if (DIALOG->Display(data.name + "SaveMaterial"))
	{
		if (DIALOG->IsOk())
		{
			string file = DIALOG->GetFilePathName();

			char path[128];
			GetCurrentDirectoryA(128, path);

			file = file.substr(strlen(path) + 1, file.length());

			wstring wfile = ToWString(file.substr(0, file.size()-4));
	
			data.height_map = wfile + L"Height.png";
			data.alpha_map = wfile + L"Alpha.png";
			height_alpha_save = true;
			Save_data(file);
		}

		DIALOG->Close();
	}
}

void Material_File_Manager::Save_data(string file)
{
	BinaryWriter* writer = new BinaryWriter(file);
	writer->String(data.name);

	writer->Vector(data.D);
	writer->Vector(data.S);
	writer->Vector(data.A);

	writer->Float(data.Shiniess);

	for (int i = 0; i < 3; i++)
	{
		writer->WString(data.DM[i]);
		writer->WString(data.SM[i]);
		writer->WString(data.NM[i]);
	}

	writer->WString(data.height_map);
	writer->WString(data.alpha_map);

	writer->WString(data.vertexShader);
	writer->WString(data.pixelShader);

	delete writer;
}

void Material_File_Manager::Load()
{
	if (ImGui::Button(("Load__" + data.name).c_str(), ImVec2({50.0f,20.0f})))
	{
		if (file_line.empty())
			file_line = "TextData/Materials/" + data.name + ".mat";

		Load_data(file_line);
	}

	ImGui::SameLine();

	if (ImGui::Button(("LoadAS__" + data.name).c_str(), ImVec2({ 50.0f,20.0f })))
	{
		DIALOG->OpenDialog(data.name + "LoadMaterial", "LoadMaterial",
			".mat", ".");
	}

	if (DIALOG->Display(data.name + "LoadMaterial"))
	{
		if (DIALOG->IsOk())
		{
			string file = DIALOG->GetFilePathName();

			char path[128];
			GetCurrentDirectoryA(128, path);

			file = file.substr(strlen(path) + 1, file.length());

			Load_data(file);
		}

		DIALOG->Close();
	}
}

void Material_File_Manager::Load_data(string file)
{
	BinaryReader* reader = new BinaryReader(file);
	if (reader->IsFailed()) {
		delete reader;
		return;
	}

	data.name = reader->String();

	data.D = reader->Vector();
	data.S = reader->Vector();
	data.A = reader->Vector();

	data.Shiniess = reader->Float();

	for (int i = 0; i < 3; i++)
	{
		data.DM[i] = reader->WString();
		data.SM[i] = reader->WString();
		data.NM[i] = reader->WString();
	}

	data.height_map = reader->WString();
	data.alpha_map = reader->WString();

	data.vertexShader = reader->WString();
	data.pixelShader = reader->WString();

	delete reader;
}

void Material_File_Manager::Create_Load()
{
	if (file_line.empty())
		file_line = "TextData/Materials/" + data.name + ".mat";

	Load_data(file_line);
}

void Material_File_Manager::SeleceMap(string name, MapType type, UINT num, ImTextureID text)
{
	if (text)
	{
		if (ImGui::ImageButton(text, ImVec2(50, 50)))
		{
			DIALOG->OpenDialog(data.name + name + to_string(num), name+to_string(num), ".png,.jpg,.tga,.jfif", ".");
		}
	}
	else
	{
		if (ImGui::Button((name + to_string(num)).c_str(), ImVec2(50, 50)))
		{
			DIALOG->OpenDialog(data.name + name+to_string(num), name+to_string(num), ".png,.jpg,.tga,.jfif", ".");
		}
	}
	
	if (DIALOG->Display(data.name + name + to_string(num)))
	{
		if (DIALOG->IsOk())
		{
			string file = DIALOG->GetFilePathName();

			char path[128];
			GetCurrentDirectoryA(128, path);

			file = file.substr(strlen(path) + 1, file.length());

			switch (type)
			{
			case MapType::DIFFUSE:
				data.DM[num] = ToWString(file);
				break;
			case MapType::SPECULAR:
				data.SM[num] = ToWString(file);
				break;
			case MapType::NORMAL:
				data.NM[num] = ToWString(file);
				break;
			}
		}

		DIALOG->Close();
	}
}

void Material_File_Manager::UnSelectMap(MapType type, UINT num)
{
	switch (type)
	{
	case MapType::DIFFUSE:
		if (ImGui::Button(("DM" + to_string(num) + "_X").c_str(), ImVec2(58, 20)))
			data.DM[num] = L"None";
		break;
	case MapType::SPECULAR:
		if (ImGui::Button(("SM" + to_string(num) + "_X").c_str(), ImVec2(58, 20)))
			data.SM[num] = L"None";
		break;
	case MapType::NORMAL:
		if (ImGui::Button(("NM" + to_string(num) + "_X").c_str(), ImVec2(58, 20)))
			data.NM[num] = L"None";
		break;
	default:
		break;
	}
}
void Material_File_Manager::Delete_Button(UINT num)
{
	UnSelectMap(DIFFUSE, num);
	ImGui::SameLine();
	UnSelectMap(SPECULAR, num);
	ImGui::SameLine();
	UnSelectMap(NORMAL, num);
}

void Material_File_Manager::GUIRender()
{
	Save();
	ImGui::SameLine();
	Load();
}
