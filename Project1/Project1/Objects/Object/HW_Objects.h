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
	// �������� ������ ������ �ش� ������Ʈ�� �Ű������� �� ������ ���ÿ� �ʿ��� �ȱ׷��� 
	// ������Ʈ�� �ʱ�ȭ ��ų��(���� ��� �ٸ���ҷ� �ű�ٴ��� ���� �ʹ� ��������
	Model* object;


};

