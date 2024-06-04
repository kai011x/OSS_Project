#pragma once

class Model : public Transform
{
public:
	Model(string name);
	~Model();

	void Update();
	void Render();
	void InstancingRender(UINT instanceCount);
	void GUIRender();

	ModelReader* Get_Reader() { return reader; }
	void Set_Color(Float4 color);
protected:
	string name;

	ModelReader* reader;
	MatrixBuffer* worldBuffer;

	vector<Vertex> gun_line;


};

