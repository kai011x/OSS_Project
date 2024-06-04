#include "Framework.h"
#include "ModelReader.h"

ModelReader::ModelReader(string name)
	: name(name)
{
	ReadMaterial();
	ReadMesh();
}

ModelReader::~ModelReader()
{
	for (Material* material : materials)
		delete material;
	for (ModelMesh* mesh : meshes)
		delete mesh;
}

void ModelReader::Render()
{
	for (ModelMesh* mesh : meshes)
		mesh->Render();
}

void ModelReader::InstancingRender(UINT instanceCount)
{
	for (ModelMesh* mesh : meshes)
		mesh->InstancingRender(instanceCount);
}

void ModelReader::SetShader(wstring file)
{
	for (Material* material : materials)
		material->SetShader(file);
}

void ModelReader::GUIRender()
{
	for(Material* material :materials)
		material->GUIRender();
}

int ModelReader::GetBone(string name)
{
	if (boneMap.count(name) == 0)
		return -1;

	return boneMap[name];
}

void ModelReader::ReadMaterial()
{
	string path = "Models/Materials/" + name + "/" + name + ".mats";

	BinaryReader* reader = new BinaryReader(path);
	if (reader->IsFailed())
		assert(false);

	UINT size = reader->UInt();
	materials.resize(size);

	for (Material*& material : materials)
	{
		material = new Material();
		string file = reader->String();
		material->Get_Save_File_Manager()->Load_data(file);
		
		material->Update_Map();
	}

	delete reader;
}

void ModelReader::ReadMesh()
{
	string path = "Models/Meshes/" + name + ".mesh";
	BinaryReader* reader = new BinaryReader(path);
	UINT size = reader->UInt();

	meshes.resize(size);
	for (ModelMesh*& mesh : meshes)
	{
		mesh = new ModelMesh(reader->String());
		UINT materialIndex = reader->UInt();
		mesh->SetMaterial(materials[materialIndex]);

		//vertex
		UINT vertexCount = reader->UInt();
		ModelVertex* vertices = new ModelVertex[vertexCount];
		reader->Byte((void**)&vertices, sizeof(ModelVertex) * vertexCount);

		//index
		UINT indexCount = reader->UInt();
		UINT* indices = new UINT[indexCount];
		reader->Byte((void**)&indices, sizeof(UINT) * indexCount);

		mesh->CreateMesh(vertices, vertexCount, indices, indexCount);
	}

	// node
	size = reader->UInt();
	nodes.resize(size);

	for (NodeData& node : nodes)
	{
		node.index = reader->Int();
		node.name = reader->String();
		node.parent = reader->Int();
		node.transform = reader->Matrix();
	}

	// bone
	size = reader->UInt();
	bones.resize(size);
	for (BoneData& bone : bones)
	{
		bone.name = reader->String();
		bone.index = reader->Int();
		bone.offset = reader->Matrix();

		boneMap[bone.name] = bone.index;
	}

	delete reader;
}
