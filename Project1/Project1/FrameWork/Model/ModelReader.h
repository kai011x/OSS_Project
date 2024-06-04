#pragma once

class ModelReader
{
public:
	ModelReader(string name);
	~ModelReader();

	void Render();
	void InstancingRender(UINT instanceCount);
	void SetShader(wstring file = L"Shaders/LandScape/TerrainEditor.hlsl");
	void GUIRender();

	int GetBone(string name);

	vector<NodeData>& GetNodes() { return nodes; }
	vector<BoneData>& GetBones() { return bones; }
	vector<Material*>& GetMaterial() { return materials; }
private:
	void ReadMaterial();
	void ReadMesh();

private:
	string name;
	vector<Material*> materials;
	vector<ModelMesh*> meshes;
	vector<NodeData> nodes;
	vector<BoneData> bones;

	map<string, UINT> boneMap;
};
