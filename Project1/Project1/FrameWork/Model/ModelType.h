#pragma once
typedef VertexUVNormalTangentBlend ModelVertex;

struct MeshData
{
	string name;
	UINT materialIndex;

	vector<ModelVertex> vertices;
	vector<UINT> indices;
};

struct NodeData
{
	int index;
	string name;
	int parent;
	Matrix transform;
};

struct BoneData
{
	string name;
	int index;
	Matrix offset;
};

struct VertexWeights
{
	UINT indices[4] = {};		//bone index
	float weights[4] = {};		// 해당 bone에 대한 보간값

	void Add(const UINT& index, const float& weight)
	{
		for (UINT i = 0; i < 4; i++)
		{
			if (weights[i] == 0.0f)
			{
				indices[i] = index;
				weights[i] = weight;
				return;
			}
		}
	}

	void Normalize()
	{
		float sum = 0.0f;

		for (UINT i = 0; i < 4; i++)
			sum += weights[i];
		
		for (UINT i = 0; i < 4; i++)
			weights[i] /= sum;
	}

};

struct KeyTransform
{
	Float3 scale;
	Float4 rotation;
	Float3 position;
};

struct KeyFrame
{
	string boneName;
	vector<KeyTransform> transforms;
};

struct ClipNode
{
	aiString name;
	vector<KeyTransform> transforms;
};

struct Clip
{
	string name;

	UINT frameCount;
	float tickPerSecond;

	vector<KeyFrame*> keyFrames;
};

struct ClipTransform
{
	Matrix transform[MAX_FRAME][MAX_BONE];

};

struct InstanceData
{
	Matrix world;
	UINT index = 0;

	InstanceData()
	{
		world = XMMatrixIdentity();
	}
};