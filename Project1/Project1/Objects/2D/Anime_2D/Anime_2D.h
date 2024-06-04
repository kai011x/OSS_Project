#pragma once

class Anime_2D : public Transform
{
private:
	typedef VertexUV VertexType;

public:
	Anime_2D(wstring file,float width, float height, Float2 left_top_pixel , Float2 right_bottom_pixel,UINT width_clip_num, UINT height_clip_num);
	~Anime_2D();

	void Update();
	void Render();
	void GUIRender();

private:
	void CreateMesh();

private:
	vector<Mesh*> meshs;
	Material* material;

	CameraBuffer* cameraBuffer;
	MatrixBuffer* worldBuffer;
	vector<vector<VertexType>> vertices;
	vector<vector<UINT>> indices;

	float width, height;

	UINT max_frame = 0;
	UINT cur_frame = 0;
	float clip_time = 0.0f;
	float frame_time = 0.2f;
	
};