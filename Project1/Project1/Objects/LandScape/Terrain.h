#pragma once

class Terrain : public GameObject
{
private:
	typedef VertexUVNormalTangent VertexType;
	const float MAX_HEIGHT = 20;

	class BrushBuffer : public ConstantBuffer
	{
	public:
		struct  Data
		{
			int type = 1;
			Float3 pickingPos = { 0,0,0 };

			float range = 10.0f;
			Float3 color = { 0,0.5f,0 };

			int camera_Use = 0;
			Float3 camera_Angle = { 0.0f,0.0f,0.0f };
		}data;

		BrushBuffer() : ConstantBuffer(&data, sizeof(Data)) {}
	};
	//class RayBuffer : public ConstantBuffer
	//{
	//public:
	//	struct  Data
	//	{
	//		Float3 position = { 0,0,0 };
	//		float triangleSize = 0.0f;

	//		Float3 direction = { 0,0,0 };
	//		float padding;
	//	}data;

	//	RayBuffer() : ConstantBuffer(&data, sizeof(Data)) {}
	//};
	struct InputDesc
	{
		Float3 v0, v1, v2;
	};
	struct OutputDesc
	{
		int picked;
		float distance;
	};
public:
	Terrain(UINT width = 100, UINT height = 100);
	~Terrain();

	void Update();
	void Render();
	void GUIRender();

	/*Vector3 Picking();
	Vector3 ComputePicking();*/

	float GetHeight(Vector3 pos);

	Float2 GetSize(){return Float2(width,height); }
private:
	void CreateMesh();
	void CreateNormal();
	void CreateTangent();
	void CreateComputeData();

	void InitNormalTangent();
	/*void AdjustHeight();*/

	// Height
	void SaveHeight(string file);
	void LoadHeight(string file);
	//void SaveHeightDialog();
	//void LoadHeightDialog();


private:
	Texture* heightMap = nullptr;
	Texture* alphaMap;
	Texture* secondMap;
	Texture* thirdMap;


	vector<VertexType> vertices;

	UINT width = 0;
	UINT height = 0;

	Vector3 pickingPos;
	Vector3 dont_find_pick = {0.0f,-100.0f,0.0f};
	BrushBuffer* brushBuffer;

	ComputeShader* computeShader;
	/*RayBuffer* rayBuffer;*/
	StructuredBuffer* structuredBuffer;

	InputDesc* input;
	OutputDesc* output;

	UINT triangleSize;
	float adjustValue = 50.0f;

	string projectPath;
	bool Click_Mode = false;

};

