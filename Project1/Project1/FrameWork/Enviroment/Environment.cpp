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
    D3D11_VIEWPORT viewPort;    // RS �ܰ� �� 1
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
    // (pi / 4) , ȭ�� ���� , ����ü�� ���� �ΰ� -> XMMatrixPerspectiveFovLH �� ����

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
    // ImGui�� �׸��� Ŀ�� ��ġ �ľ����� ����
    ImVec2 p = ImGui::GetCursorScreenPos();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    
    // ��ư ũ�� ���ϴ� ������ ����
    float height = ImGui::GetFrameHeight();
    float width = height * 1.55f;
    float radius = height * 0.50f;
    
    // InvisibleButton���� a�� ������ �ش� ��ư�� �ּҰ����� ���� �ش簪�� � Ư����
    // ���� ��� �� �Լ� ������ Ư�������� ������ �Է��ϸ� 2���� ��ư�� ���� 1���� ��ư�� �۵��ϰ� ��
    if (ImGui::InvisibleButton(a, ImVec2(width, height)))
        *v = !*v;
    ImU32 col_bg;   // ��ư�� �÷�
    if (ImGui::IsItemHovered())
        col_bg = *v ? IM_COL32(145 + 20, 211, 68 + 20, 255) : IM_COL32(218 - 20, 218 - 20, 218 - 20, 255);
    else
        col_bg = *v ? IM_COL32(145, 211, 68, 255) : IM_COL32(218, 218, 218, 255);
    
    // ���� ä���� �簢���� �׸�
    draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
    // �簢���� ���ʿ� ���� �׸��� ���ʿ� ���ʰ� �����ʿ� on off�� Ȯ���ϴ� �� �׸��� �׸��� ������ ������
    draw_list->AddCircleFilled(ImVec2(*v ? (p.x + width - radius) : (p.x + radius), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));
}


