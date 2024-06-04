#pragma once

class ModelInstansing
{
private:


public:
	ModelInstansing(string name);
	~ModelInstansing();

	void Update();
	void Render();
	void GUIRender();
	
	Transform* Add();

private:
	string name;

	ModelReader* reader;

	vector<Transform*> transforms;
	InstanceData instanceDatas[MAX_INSTANCE];

	VertexBuffer* instanceBuffer;

	UINT drawCount = 0;
};
