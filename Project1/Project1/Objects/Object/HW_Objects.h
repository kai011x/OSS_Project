#pragma once

class HW_Objects : public Transform
{
public:
	HW_Objects(string name);
	~HW_Objects();

	void Update();
	void Render();
	void GUIRender();

	Model* Get_Object() { return object;}
private:
	// 오브젝의 고유의 정보와 해당 오브젝트를 옮겼을때의 그 정보가 동시에 필요함 안그러면 
	// 오브젝트를 초기화 시킬때(예를 들어 다른장소로 옮긴다던지 값이 너무 끔찍해짐
	Model* object;


};

