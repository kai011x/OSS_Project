#pragma once

class Quad : public GameObject
{
private:
	typedef VertexUVNormalTangent VertexType;

public:
	Quad(Float2 size = {1.0f,1.0f});
	~Quad();

	void Render();
	Float2 GetSize() { return size; }

private:
	void CreateMesh();

private:
	Float2 size;
	CameraBuffer* cameraBuffer;
	MosterLightBuffer* monsterLightBuffer;
	vector<VertexType> vertices;
};

