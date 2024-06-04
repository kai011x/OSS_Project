#pragma once

// Environment

class Environment : public Singleton<Environment>
{
public:
	Environment();
	~Environment();

	void Update();
	void GUIRender();

	void Set();
	void PostSet();

private:
	void CreateViewport();
	void CreateProjection();
	void CreateState();

public:
	void Set_off()
	{
		isWireMode = false;
		rasterizerState->FillMode(D3D11_FILL_SOLID);
		rasterizerState->SetState();
	}
	void Set_on()
	{
		isWireMode = true;
		rasterizerState->FillMode(D3D11_FILL_WIREFRAME);
		rasterizerState->SetState();
	}

	Matrix GetProjection() { return projection; }
	Camera* GetMainCamera() { return mainCamera; }

private:
	BlendState* blendState;

	Matrix Camera_view;
	Matrix projection;

	Camera* mainCamera;
	MatrixBuffer* perspectiveBuffer;

	LightBuffer* lightBuffer;

	MatrixBuffer* uiViewBuffer;
	MatrixBuffer* orthographicBuffer;

	D3D11_VIEWPORT viewport;

	SamplerState* samplerState;
	RasterizerState* rasterizerState;

	DepthStencilState* depthState[2];	//적용한거 적용안한거 2개

	Float4 Save_specular = {0.0f,0.0f,0.0f,0.0f};

	bool isWireMode = false;
	void toggle_Buttom(const char* a,bool* v);
	bool normal_print = true;
	bool specular_print = true;

};