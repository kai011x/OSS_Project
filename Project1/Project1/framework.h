#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
#define PI 3.141592
#define GRAVITE 9.8

#define CENTER_X WIN_WIDTH * 0.5f
#define CENTER_Y WIN_HEIGHT * 0.5f

#define MAX_BONE 512
#define MAX_FRAME 512
#define MAX_INSTANCE 100

#define DEVICE Device::Get()->GetDevice()
#define DC Device::Get()->GetDeviceContext()

#define DELTA ImGui::GetIO().DeltaTime

#define KEY_PRESS(k) ImGui::IsKeyDown(k)
#define KEY_DOWN(k) ImGui::IsKeyPressed(k, false)
#define KEY_UP(k) ImGui::IsKeyReleased(k)

////0 : 좌클릭, 1: 우클릭, 2 : 중간클릭
//#define MOUSE_PRESS(k) ImGui::IsMouseDown(k)
//#define MOUSE_CLICK(k) ImGui::IsMouseClicked(k)
//#define MOUSE_DBCLICK(k) ImGui::IsMouseDoubleClicked(k)
//#define MOUSE_UP(k) ImGui::IsMouseReleased(k)

#define SCENE SceneManager::Get()
#define CAMERA Environment::Get()->GetMainCamera()
#define DIALOG ImGuiFileDialog::Instance()
// 선형 보관 : s부터e를 선으로 이은후 중간의 t만큼의 위치를 구하는 것
#define LERP(s,e,t)(s + (e - s)* t)


#define HW_CHARACTER HW_Object_Character::Get()
#define HW_MAP HW_Map_Manager::Get()


// Windows 헤더 파일
#include <windows.h>



//STL
#include <vector>
#include <map>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <assert.h>
#include <functional>
#include <fstream>	// csv는 이걸로 

//DirectX
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXCollision.h>

// 핵심 라이브러리
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"dxguid.lib") // guid에 대한 정보가 있는 lib

//DirectXTex
#include <DirectXTex/DirectXTex.h>

#pragma comment(lib,"DirectXTex.lib")

//ImGui
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <ImGuiFileDialog.h>

#pragma comment(lib, "ImGui.lib")

//Assimp
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>

#pragma comment(lib,"assimp-vc143-mtd.lib")



using namespace std;
using namespace DirectX;
using namespace DirectX::TriangleTests;

typedef XMFLOAT4 Float4;
typedef XMFLOAT3 Float3;
typedef XMFLOAT2 Float2;

typedef XMMATRIX Matrix;
typedef XMFLOAT4X4 Float4x4;
typedef XMVECTOR Vector4;

typedef function<void()> FP_Event;
typedef function<void(void*)> ParamEvent;


//Framework header
#include "FrameWork/Utility/Singleton.h"
#include "FrameWork/Utility/Utility"
#include "FrameWork/Utility/BinaryReader.h"
#include "FrameWork/Utility/BinaryWriter.h"

#include "FrameWork/Device/Device.h"

using namespace Utility;

/*============== Shader ================*/
#include "FrameWork/Shader/Shader.h"
#include "FrameWork/Shader/VertexShader.h"
#include "FrameWork/Shader/PixelShader.h"
#include "FrameWork/Shader/ComputeShader.h"
/*============= Buffer ==================*/
#include "FrameWork/Buffer/VertexBuffer.h"
#include "FrameWork/Buffer/IndexBuffer.h"
#include "FrameWork/Buffer/ConstBuffer.h"
#include "FrameWork/Buffer/GlobalBuffer.h"
#include "FrameWork/Buffer/VertexLayout.h"
#include "FrameWork/Buffer/RawBuffer.h"
#include "FrameWork/Buffer/StructuredBuffer.h"
/*============== State ====================*/
#include "FrameWork/State/SamplerState.h"
#include "FrameWork/State/RasterizerState.h"
#include "FrameWork/State/BlendState.h"
#include "FrameWork/State/DepthStencilState.h"
/*===============Render =======================*/
#include "FrameWork/Render/Mesh.h"
#include "FrameWork/Render/Texture.h"

// Object material manager
#include "Objects/Material//Material_File_Manager.h"	
#include "FrameWork/Render/Material.h"

// 충돌계산용
#include "FrameWork/Math/Vector3.h"
#include "Framework/Math/GameMath.h"
#include "FrameWork/Math/Transform.h"

// Model
#include "FrameWork/Model/ModelType.h"
#include "FrameWork/Model/ModelMesh.h"
#include "FrameWork/Model/ModelReader.h"
#include "FrameWork/Model/Model.h"
#include "FrameWork/Model/ModelInstancing.h"

#include "FrameWork/Collision/Collider.h"
#include "FrameWork/Collision/BoxCollider.h"
#include "FrameWork/Collision/SphereCollider.h"
#include "FrameWork/Collision/CapsuleCollider.h"

using namespace GameMath;


#include "FrameWork/Enviroment/Camera.h"
#include "FrameWork/Enviroment/Environment.h"

// 알고리즘
#include "Algorithm/Node.h"
#include "Algorithm/Heap.h"
#include "Algorithm/AStar.h"

//GameObject Header
#include "Objects/Basic/GameObject.h"
#include "Objects/Basic/Quad.h"
#include "Objects/Basic/Cube.h"
#include "Objects/Basic/Grid.h"
#include "Objects/Basic/Sphere.h"
#include "Objects/Basic/ModelObject.h"
#include "Objects/LandScape/Terrain.h"

#define INFO_TEXT(k,c) ImGui::TextColored(c,k.c_str());

// 2D 관련
#include "Objects/2D/Anime_2D/Anime_2D.h"

#include "Objects/Object/HW_Objects.h"
#include "Objects/Object/Collider/HW_RectCollider.h" //맵, 캐릭터, 몬스터 충돌 처리하기 위한 평면
#include "Objects/Character/HW_Basic_Character.h"	// 기본 캐릭터	// 모델, collider, hp바만 가지고 있음

// 기본 오브젝트(맵에서 쓸꺼)
#include "Objects/Dungeon/HW_Dungeon.h"
#include "Objects/Dungeon/HW_Pacman_Map.h"

#include "Objects/Character/Character/HW_Character_Transform.h"	// 매우 기본적인 캐릭터
#include "Objects/Character/Character/HW_Hero.h"

#include "Objects/Character/Monster/PackMan_Monster/HW_Packman_Monster.h"

#include "Objects/Singleton/HW_Object_Character.h"
#include "Objects/Singleton/HW_Map_Manager.h"

#include "Objects/DataManager//DataManager.h"

// Scene Header
//#include "Scene/Scene.h"
#include "Managers/GameManager.h"
#include "Managers/SceneManager.h"


extern HWND hWnd;	//-> 얘가 전역이라고 말해주는 것 / *이미 존재하는 변수에 사용*
extern Vector3 mousePos;

