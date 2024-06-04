#pragma once

class Camera : public Transform
{
public:
	Camera();
	~Camera();

	void Update();
	void GUIRender();

	void SetViewBuffer();

	Ray ScreenPointToRay(Vector3 screenPos);
	void SetTarget(Transform* target) { this->target = target; }

	Vector3 WorldToScreenPoint(Vector3 worldPos);
	Vector3 Picking_pos;
	float Get_Eye_Sight() { return eyesight; }
private:
	//void FollowMode();
	//void FreeMode();
	void First_Person_View_Mode();

private:
	float moveSpeed = 30.0f;
	float rotSpeed = 1.0f;
	float wheelSpeed = 10.0f;

	ViewBuffer* viewBuffer;
	Matrix view;
	Matrix invView;

	Transform* target = nullptr;

	float distance = 20.0f;
	float height = 10.0f;

	float rotY = PI;
	float rotYOffset = PI;

	float destRot = 0.0f;
	Vector3 destPos;

	Vector3 focusOffset;

	Matrix rotMatrix;

	float moveDamping = 5.0f;
	float rotDamping = 5.0f;

	int mode_Select = 2;

	int temp = 0;

	float eyesight = 20.0f;
};
