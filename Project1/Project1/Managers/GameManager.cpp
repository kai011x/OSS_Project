#include "Framework.h"

#include "Scene/GridScene.h"
#include "Scene/HW_Scene.h"


GameManager::GameManager()
{
	Create();

	SCENE->Create("Grid", new GridScene());
	SCENE->Create("Start", new HW_Scene());

	SCENE->Add("Grid");
	SCENE->Add("Start");
}

GameManager::~GameManager()
{
	Delete();
}

void GameManager::Update()
{
	Environment::Get()->Update();

	SCENE->Update();
}

void GameManager::Render()
{
	SCENE->PreRender();

	Device::Get()->Clear();
	Environment::Get()->Set();
	SCENE->Render();

	Environment::Get()->PostSet();
	SCENE->PostRender();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	{	// 클릭시 나올 캐릭터 정보나 그런것은 여기서 적을 것
		ImGui::Begin("information");
	
		SCENE->InfoRender();
		ImGui::End();
	}


	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::Get()->Present();
}

void GameManager::Create()
{
	Device::Get();
	Environment::Get();

	HW_Map_Manager::Get();
	HW_Object_Character::Get();

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(DEVICE, DC);
}

void GameManager::Delete()
{
	Device::Delete();
	Environment::Delete();
	Texture::Delete();
	Shader::Delete();

	HW_Map_Manager::Delete();
	

	HW_Object_Character::Delete();
	SceneManager::Delete();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

