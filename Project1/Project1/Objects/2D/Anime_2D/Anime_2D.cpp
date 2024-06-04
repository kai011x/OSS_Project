#include "Framework.h"
#include "Anime_2D.h"

Anime_2D::Anime_2D(wstring file, float width, float height, Float2 left_top_pixel, Float2 right_bottom_pixel, UINT width_clip_num, UINT height_clip_num)
	: width(width), height(height)
{
	worldBuffer = new MatrixBuffer();
	material = new Material();
	cameraBuffer = new CameraBuffer();
	material->SetDiffuseMap(file);
	material->SetShader(L"Shaders/HomeworkShaders/PackMan_Shader/PackMan_Monster_Shader.hlsl");

	UINT width_texture = material->GetDMap(0)->Width();
	UINT height_texture = material->GetDMap(0)->Height();

	float u_temp = (right_bottom_pixel.x - left_top_pixel.x) / (width_texture*width_clip_num);	//x축 u값의 한칸
	float v_temp = (left_top_pixel.y - right_bottom_pixel.y) / (height_texture*height_clip_num); // y축 v값 한칸의 값

	float u_basis = left_top_pixel.x / width_texture;
	float v_basis = right_bottom_pixel.y / height_texture;
	Float2 halfSize;
	halfSize.x = width * 0.5f;
	halfSize.y = height * 0.5f;

	for (UINT x = 0; x < width_clip_num; x++)
	{
		for (UINT y = 0; y < height_clip_num; y++)
		{
			// -- -+ ++ +- 순으로 0,1,2,0,2,3의 인덱스를 가며 tagent는 다른 축으로 +1 normal은 그 반대이다.
			vector<VertexType> vertex_temp;

			VertexType vertex;
			vertex.pos = { -halfSize.x , -halfSize.y , 0.0f };
			vertex.uv = { x * u_temp + u_basis , (y + 1) * v_temp + v_basis };

			vertex_temp.push_back(vertex);

			vertex.pos = { -halfSize.x , +halfSize.y , 0.0f };
			vertex.uv = { x * u_temp + u_basis, y * v_temp + v_basis };

			vertex_temp.push_back(vertex);

			vertex.pos = { +halfSize.x , +halfSize.y , 0.0f };
			vertex.uv = { (x+1) * u_temp + u_basis, y * v_temp + v_basis };

			vertex_temp.push_back(vertex);

			vertex.pos = { +halfSize.x , -halfSize.y , 0.0f };
			vertex.uv = { (x + 1) * u_temp + u_basis,(y + 1) * v_temp + v_basis };

			vertex_temp.push_back(vertex);

			vector<UINT> indices_temp;
			indices_temp = { 0,1,2,0,2,3 };

			indices.push_back(indices_temp);
			vertices.push_back(vertex_temp);

			Mesh* mesh = new Mesh(vertices[max_frame].data(), sizeof(VertexType), vertices[max_frame].size(), 
									indices[max_frame].data(), indices[max_frame].size());
			meshs.push_back(mesh);
			max_frame++;
		}
	}

	frame_time = 1.0f / (float)max_frame;
}

Anime_2D::~Anime_2D()
{
	delete material;
	delete worldBuffer;
	delete cameraBuffer;
}

void Anime_2D::Update()
{
	this->UpdateWorld();

	this->clip_time += DELTA;
	if (clip_time > frame_time)
	{
		clip_time = 0.0f;
		cur_frame++;
		if (cur_frame >= max_frame)
			cur_frame = 0;
	}

	cameraBuffer->data.camera_Pos = CAMERA->GlobalPos();
	cameraBuffer->data.lenght = CAMERA->Get_Eye_Sight();
}

void Anime_2D::Render()
{
	if (!Active()) return;

	cameraBuffer->SetPSBuffer(9);

	worldBuffer->Set(world);
	worldBuffer->SetVSBuffer(0);

	meshs[cur_frame]->IASet();
	material->Set();

	DC->DrawIndexed(indices[cur_frame].size(), 0, 0);
}

void Anime_2D::GUIRender()
{
}

void Anime_2D::CreateMesh()
{
}
