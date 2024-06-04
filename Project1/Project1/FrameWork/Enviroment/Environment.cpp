#include "Framework.h"


Environment::Environment()
{
	CreateViewport();
    CreateProjection();
    CreateState();

    mainCamera = new Camera();
    mainCamera->Tag() = "mainCamera";
    mainCamera->Load();

    lightBuffer = new LightBuffer();
    uiViewBuffer = new MatrixBuffer();
}

Environment::~Environment()
{
    mainCamera->Save();

    delete mainCamera;
	delete perspectiveBuffer;
    delete orthographicBuffer;
    delete uiViewBuffer;
    delete samplerState;
    delete lightBuffer;
 
}

void Environment::Update()
{
    if (KEY_DOWN(ImGuiKey_F1))
    {
        if (isWireMode)
        {
            isWireMode = false;
            rasterizerState->FillMode(D3D11_FILL_SOLID);
        }
        else
        {
            isWireMode = true;
            rasterizerState->FillMode(D3D11_FILL_WIREFRAME);
        }

        rasterizerState->SetState();
    }

    if (KEY_DOWN(ImGuiKey_F2))
    {
        Collider::SwitchRender();
    }

    mainCamera->Update();

    //Set();
}

void Environment::GUIRender()
{
    string fps = "FPS : " + to_string((int)ImGui::GetIO().Framerate);
    ImGui::Text(fps.c_str());

    string mouse = "Mouse.x : " + to_string((int)ImGui::GetMousePos().x);
    ImGui::Text(mouse.c_str());
    mouse = "Mouse.y : " + to_string((int)ImGui::GetMousePos().y);
    ImGui::Text(mouse.c_str());

    mainCamera->GUIRender();

}

void Environment::Set()
{
    mainCamera->SetViewBuffer();
    lightBuffer->SetPSBuffer(0);
    perspectiveBuffer->SetVSBuffer(2);

    depthState[0]->SetState();
}

void Environment::PostSet()
{
    uiViewBuffer->SetVSBuffer(1);
    orthographicBuffer->SetVSBuffer(2);
    
    depthState[1]->SetState();
}

void Environment::CreateViewport()
{
    D3D11_VIEWPORT viewPort;    // RS 단계 중 1
    viewPort.Width = WIN_WIDTH;
    viewPort.Height = WIN_HEIGHT;
    viewPort.MaxDepth = 1.0f;
    viewPort.MinDepth = 0.0f;
    viewPort.TopLeftX = 0.0f;
    viewPort.TopLeftY = 0.0f;

    DC->RSSetViewports(1, &viewPort);
}

void Environment::CreateProjection()
{
    projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 1000.0f);
    // (pi / 4) , 화면 비율 , 절두체의 비율 두개 -> XMMatrixPerspectiveFovLH 의 인자

    perspectiveBuffer = new MatrixBuffer();
    perspectiveBuffer->Set(projection);

    Matrix ortho = XMMatrixOrthographicOffCenterLH(0.0f, WIN_WIDTH, 0.0f, WIN_HEIGHT, -1.0f, 1.0f);

    orthographicBuffer = new MatrixBuffer();
    orthographicBuffer->Set(ortho);

}

void Environment::CreateState()
{
    samplerState = new SamplerState();
    samplerState->PSSetState(0);

    rasterizerState = new RasterizerState();

    blendState = new BlendState();
    blendState->Alpha(true);
    blendState->SetState();

    depthState[0] = new DepthStencilState();
    depthState[1] = new DepthStencilState();
    depthState[1]->DepthEnable(false);
}

void Environment::toggle_Buttom(const char* a ,bool* v)
{
    // ImGui의 그림과 커서 위치 파악으로 추정
    ImVec2 p = ImGui::GetCursorScreenPos();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    
    // 버튼 크기 구하는 것으로 추정
    float height = ImGui::GetFrameHeight();
    float width = height * 1.55f;
    float radius = height * 0.50f;
    
    // InvisibleButton에서 a의 역할은 해당 버튼의 주소값으로 추정 해당값을 어떤 특정값
    // 예를 들어 이 함수 내에서 특정값으로 지정후 입력하면 2개의 버튼을 만들어도 1개의 버튼만 작동하게 됨
    if (ImGui::InvisibleButton(a, ImVec2(width, height)))
        *v = !*v;
    ImU32 col_bg;   // 버튼의 컬러
    if (ImGui::IsItemHovered())
        col_bg = *v ? IM_COL32(145 + 20, 211, 68 + 20, 255) : IM_COL32(218 - 20, 218 - 20, 218 - 20, 255);
    else
        col_bg = *v ? IM_COL32(145, 211, 68, 255) : IM_COL32(218, 218, 218, 255);
    
    // 속이 채워진 사각형을 그림
    draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
    // 사각형에 양쪽에 원을 그리고 안쪽에 왼쪽과 오른쪽에 on off를 확인하는 원 그림을 그리는 것으로 추정중
    draw_list->AddCircleFilled(ImVec2(*v ? (p.x + width - radius) : (p.x + radius), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));
}


