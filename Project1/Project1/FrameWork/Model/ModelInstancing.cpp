#include "Framework.h"
#include "ModelInstancing.h"

ModelInstansing::ModelInstansing(string name)
	:name(name)
{
	instanceBuffer = new VertexBuffer(instanceDatas,sizeof(InstanceData),MAX_INSTANCE);

	reader = new ModelReader(name);
	reader->SetShader(L"Shaders/Instancing/ModelInstancing.hlsl");

}

ModelInstansing::~ModelInstansing()
{
	for (Transform* transform : transforms)
		delete transform;
}

void ModelInstansing::Update()
{
	drawCount = 0;

	for (UINT i = 0; i < transforms.size(); i++)
	{
		if (transforms[i]->Active())
		{
			transforms[i]->UpdateWorld();
			instanceDatas[drawCount].world = XMMatrixTranspose(transforms[i]->GetWorld());
			instanceDatas[drawCount].index = i;
			drawCount++;
		}
	}
	instanceBuffer->Update(instanceDatas, drawCount);
}

void ModelInstansing::Render()
{
	instanceBuffer->IASet(1);
	reader->InstancingRender(drawCount);
}

void ModelInstansing::GUIRender()
{
	ImGui::Text("DrawCount : %d", drawCount);

	for (Transform* transform : transforms)
	{
		transform->GUIRender();
	}
}

Transform* ModelInstansing::Add()
{
	Transform* transform = new Transform();
	transform->Tag() = name + "_" + to_string(transforms.size());
	transforms.push_back(transform);

	return transform;
}
