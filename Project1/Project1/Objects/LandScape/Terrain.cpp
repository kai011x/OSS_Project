#include "Framework.h"

Terrain::Terrain(UINT width, UINT height) : GameObject(L"Shaders/LandScape/Terrain.hlsl"), width(width), height(height)
{
	CreateMesh();
	CreateComputeData();

	brushBuffer = new BrushBuffer();

	material->SetDiffuseMap(L"Textures/Landscape/Dirt2.png");

	alphaMap = Texture::Add(L"Textures/HeightMaps/AlphaMap.png");
	secondMap = Texture::Add(L"Textures/Landscape/Dirt.png");
	thirdMap = Texture::Add(L"Textures/Landscape/Stones.png");

	char path[128];
	GetCurrentDirectoryA(128, path);

	projectPath = path;
}

Terrain::~Terrain()
{
	delete brushBuffer;

	delete structuredBuffer;
	delete[] input;
	delete[] output;
}

void Terrain::Update()
{

}

void Terrain::Render()
{
	brushBuffer->SetPSBuffer(10);
	this->Render();

	alphaMap->PSSet(10);
	secondMap->PSSet(11);
	thirdMap->PSSet(12);

}
void Terrain::GUIRender()
{

}
void Terrain::CreateMesh()
{
	vector<Float4> pixels(width * height, Float4(0, 0, 0, 0));


	if (heightMap)
	{
		width = heightMap->Width();
		height = heightMap->Height();

		heightMap->ReadPixels(pixels);
	}

	vertices.clear();
	indices.clear();

	//vertices
	for (UINT z = 0; z < height; z++)
	{
		for (UINT x = 0; x < width; x++)
		{
			VertexType vertex;
			vertex.pos = { (float)x, 0.0f,  (float)z };
			vertex.uv.y = x / (float)(width - 1);
			vertex.uv.x = z / (float)(height - 1);

			UINT index = width * z + x;
			vertex.pos.y = pixels[index].x * MAX_HEIGHT;

			vertices.emplace_back(vertex);
		}
	}


	//indeices
	for (UINT z = 0; z < (width - 1); z++)
	{
		for (UINT x = 0; x < (height - 1); x++)
		{
			indices.push_back(width * z + x);	// 0
			indices.push_back(width * z + x + width);	// 4
			indices.push_back(width * z + x + width + 1);	// 5

			indices.push_back(width * z + x);				// 0
			indices.push_back(width * z + x + width + 1);	// 5
			indices.push_back(width * z + x + 1);			// 1
		}
	}

	CreateNormal();
	CreateTangent();

	mesh = new Mesh(vertices.data(), sizeof(VertexType), (UINT)vertices.size(),
		indices.data(), (UINT)indices.size());
}

void Terrain::CreateNormal()
{
	for (UINT i = 0; i < indices.size() / 3 ; i++)
	{
		UINT index0 = indices[i*3];
		UINT index1 = indices[i*3 + 1];
		UINT index2 = indices[i*3 + 2];

		Vector3 v0 = vertices[index0].pos;
		Vector3 v1 = vertices[index1].pos;
		Vector3 v2 = vertices[index2].pos;

		Vector3 A = v1 - v0;
		Vector3 B = v2 - v0;
		
		Vector3 normal = Vector3::Cross(A, B).Normalize();

		vertices[index0].normal += normal;
		vertices[index1].normal += normal;
		vertices[index2].normal += normal;
	}

}
void Terrain::CreateTangent()
{
	for (UINT i = 0; i < indices.size() / 3; i++)
	{
		UINT index0 = indices[i * 3 + 0];
		UINT index1 = indices[i * 3 + 1];
		UINT index2 = indices[i * 3 + 2];

		VertexType vertex0 = vertices[index0];
		VertexType vertex1 = vertices[index1];
		VertexType vertex2 = vertices[index2];

		Vector3 p0 = vertex0.pos;
		Vector3 p1 = vertex1.pos;
		Vector3 p2 = vertex2.pos;

		Float2 uv0 = vertex0.uv;
		Float2 uv1 = vertex1.uv;
		Float2 uv2 = vertex2.uv;

		Vector3 e0 = p1 - p0;
		Vector3 e1 = p2 - p0;

		float u0 = uv1.x - uv0.x;
		float v0 = uv1.y - uv0.y;
		float u1 = uv2.x - uv0.x;
		float v1 = uv2.y - uv0.y;

		float d = (1.0f) / (u0 * v1 - v0 * u1);

		Vector3 tangent = d * (e0 * v1 - e1 * v0);

		vertices[index0].tangent += tangent;
		vertices[index1].tangent += tangent;
		vertices[index2].tangent += tangent;
	}

	// tangent 보정단계
	for (VertexType& vertex : vertices)
	{
		Vector3 t = vertex.tangent;
		Vector3 n = vertex.normal;

		vertex.tangent = (t - n * Vector3::Dot(n, t)).Normalize();
	}
}
void Terrain::CreateComputeData()
{
	computeShader = Shader::AddCS(L"Shaders/Compute/Picking.hlsl");

	triangleSize = indices.size() / 3;

	input = new InputDesc[triangleSize];
	output = new OutputDesc[triangleSize];

	for (UINT i = 0; i < triangleSize; i++)
	{
		UINT index0 = indices[i * 3 + 0];
		UINT index1 = indices[i * 3 + 1];
		UINT index2 = indices[i * 3 + 2];

		input[i].v0 = vertices[index0].pos;
		input[i].v1 = vertices[index1].pos;
		input[i].v2 = vertices[index2].pos;

	}

	structuredBuffer = new StructuredBuffer(input, sizeof(InputDesc), triangleSize, sizeof(OutputDesc), triangleSize);

}
void Terrain::InitNormalTangent()
{
	for (VertexType& vertex : vertices)
	{
		vertex.normal = Vector3();
		vertex.tangent = Vector3();
	}
}


void Terrain::SaveHeight(string file)
{
	UINT size = width * height * 4;
	uint8_t* pixels = new uint8_t[size];

	for (UINT i = 0; i < size / 4; i++)
	{
		float y = vertices[i].pos.y;

		uint8_t height = y / MAX_HEIGHT * 255;

		pixels[i * 4 + 0] = height;
		pixels[i * 4 + 1] = height;
		pixels[i * 4 + 2] = height;
		pixels[i * 4 + 3] = 255;
	}

	Image image;
	image.width = width;
	image.height = height;
	image.pixels = pixels;
	image.format = DXGI_FORMAT_R8G8B8A8_UNORM;
	image.rowPitch = width * 4;
	image.slicePitch = size;

	SaveToWICFile(image, WIC_FLAGS_FORCE_RGB, GetWICCodec(WIC_CODEC_PNG),
		ToWString(file).c_str());
}
void Terrain::LoadHeight(string file)
{
	heightMap = Texture::Add(ToWString(file));

	delete mesh;

	CreateMesh();

	delete structuredBuffer;
	delete[] input;
	delete[] output;

	CreateComputeData();
}




float Terrain::GetHeight(Vector3 pos)
{
	int x = (int)pos.x;
	int z = (int)pos.z;

	if (x < 0 || x >= width - 1)return 0.0f;
	if (z < 0 || z >= height - 1)return 0.0f;

	UINT index[4];
	index[0] = width * z + x;
	index[1] = width * (z + 1) + x;
	index[2] = width * z + x + 1;
	index[3] = width * (z + 1) + x + 1;

	Vector3 p[4];
	for (UINT i = 0; i < 4; i++)
		p[i] = vertices[index[i]].pos;

	float u = pos.x - p[0].x;
	float v = pos.z - p[0].z;

	Vector3 result;
	if (u + v <= 1.0f)
	{
		result = (((p[2] - p[0]) * u) + ((p[1] - p[0]) * v)) + p[0];
	}
	else
	{
		u = 1.0f - u;
		v = 1.0f - v;

		result = (((p[2] - p[3]) * u) + ((p[1] - p[3]) * v)) + p[3];
	}

	return result.y;
}
