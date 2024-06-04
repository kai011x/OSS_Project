#include "Framework.h"
#include "Camera.h"

Camera::Camera()
{
	viewBuffer = new ViewBuffer();
	view = XMMatrixIdentity();
}

Camera::~Camera()
{
	delete viewBuffer;
}

void Camera::Update()
{
	First_Person_View_Mode();

}

void Camera::GUIRender()
{
	if (ImGui::TreeNode("CameraOption"))
	{
		ImGui::Indent();
		ImGui::SliderInt("Camera_Mode", &mode_Select, 0, 2);

		ImGui::InputFloat3("Campos", (float*)&Position(), "%.0f");
		ImGui::InputFloat3("CamRot", (float*)&Rotation(), "%.0f");
		ImGui::DragFloat("CamMoveSpeed", &moveSpeed);
		ImGui::DragFloat("CamrotSpeed", &rotSpeed);
		ImGui::DragFloat("CamwheelSpeed", &wheelSpeed);
		ImGui::DragFloat("EyeSight", &eyesight);

		ImGui::Unindent();

		if (target && ImGui::TreeNode("TargetOption"))
		{
			ImGui::DragFloat("Distance", &distance, 0.1f);
			ImGui::DragFloat("Height", &height, 0.1f);
			ImGui::DragFloat3("FocusOffset", (float*)&focusOffset, 0.1f);

			float degree = XMConvertToDegrees(rotY);
			ImGui::DragFloat("RotationY", &degree,0.1f);
			rotY = XMConvertToRadians(degree);

			ImGui::DragFloat("MoveDamping", &moveDamping, 0.1f);
			ImGui::DragFloat("RotDamping", &rotDamping, 0.1f);

			ImGui::TreePop();
		}

		ImGui::TreePop();
	}
}

void Camera::SetViewBuffer()
{
	viewBuffer->SetVSBuffer(1);
}

//Ray Camera::ScreenPointToRay(Vector3 screenPos)
//{
//	Float2 screenSize(WIN_WIDTH, WIN_HEIGHT);
//
//	Float2 point;	// -1~1 ��ũ����ǥ->NDC��ǥ
//	point.x = (2.0f * (screenPos.x / screenSize.x)) - 1.0f;
//	point.y = (2.0f * (screenPos.y / screenSize.y)) - 1.0f;
//
//	Matrix projection = Environment::Get()->GetProjection();
//
//	Float4x4 temp;
//	XMStoreFloat4x4(&temp, projection);
//
//	point.x /= temp._11;	// ���򿡴��� ������
//	point.y /= temp._22;	// ������ ���� ������
//
//	Vector3 tempPos(point.x, point.y , 1.0f);
//
//	Ray ray;
//	ray.position = Position();
//	ray.direction = (tempPos * invView).Normalize();
//
//	return ray;
//}

//Vector3 Camera::WorldToScreenPoint(Vector3 worldPos)
//{
//	Vector3 screenPos;
//
//	screenPos = XMVector3TransformCoord(worldPos, view);
//	screenPos = XMVector3TransformCoord(screenPos, Environment::Get()->GetProjection());
//	//��� : NDC ������ǥ : -1 ~ 1 -> 0~ WIN_WIDTH�� ��������
//	screenPos.x = (screenPos.x + 1.0f) * 0.5f;
//	screenPos.y = (screenPos.y + 1.0f) * 0.5f;
//	screenPos.z = (screenPos.z + 1.0f) * 0.5f;
////	screenPos.y *= -1;
//
//	screenPos.x *= WIN_WIDTH;
//	screenPos.y *= WIN_HEIGHT;
//
//	return screenPos;
//}

//void Camera::FreeMode()
//{
//	if (MOUSE_PRESS(1))
//	{
//		if (KEY_PRESS(ImGuiKey_W)){
//			this->Position() += Up() * moveSpeed * DELTA;
//		}
//		if (KEY_PRESS(ImGuiKey_S)){
//			this->Position() -= Up() * moveSpeed * DELTA;
//		}
//		if (KEY_PRESS(ImGuiKey_A)){
//			this->Position() -= Right()* moveSpeed * DELTA;
//		}
//		if (KEY_PRESS(ImGuiKey_D)){
//			this->Position() += Right() * moveSpeed * DELTA;
//		}
//		if (KEY_PRESS(ImGuiKey_Q)){
//			this->Position() += Forward() * moveSpeed * DELTA;
//		}
//		if (KEY_PRESS(ImGuiKey_E)){
//			this->Position() -= Forward() * moveSpeed * DELTA;
//		}
//
//		ImVec2 delta = ImGui::GetIO().MouseDelta;
//
//		Rotation().x += delta.y * rotSpeed * DELTA;
//		Rotation().y += delta.x * rotSpeed * DELTA;
//
//	}
//
//	this->UpdateWorld();
//	invView = world;
//	view = XMMatrixInverse(nullptr, world);
//	viewBuffer->Set(view , world);
//}

void Camera::First_Person_View_Mode()
{
	// terget���� terget forward�� ���� ���� ���鲨

	destRot = target->Rotation().y;
	this->Rotation().y = destRot + rotY;

	rotMatrix = XMMatrixRotationY(this->Rotation().y);

	Vector3 forward = Vector3(0, 0, 1) * rotMatrix;

	destPos = target->GlobalPos();
	destPos.y += 3.0f;
//	destPos.y += 1.65f;
//	destPos += forward * 0.2f;

	this->Position() = destPos;

	Vector3 offset = XMVector3TransformCoord(focusOffset, rotMatrix);
	view = XMMatrixLookAtLH(this->Position(), this->Position() + (forward* 10), Vector3(0, 1, 0));

	invView = XMMatrixInverse(nullptr, view);
	viewBuffer->Set(view, invView);

	this->UpdateWorld();
}

//void Camera::FollowMode()
//{
//	destRot = LERP(destRot,target->Rotation().y,rotDamping*DELTA);
//	this->Rotation().y = destRot + rotY;
//
//	rotMatrix = XMMatrixRotationY(this->Rotation().y);
//
//	Vector3 forward = Vector3(0, 0, 1) * rotMatrix;
//
//	destPos = forward * -distance + target->GlobalPos();
//	destPos.y += height;
//
//	this->Position() = LERP(Position(),destPos,moveDamping * DELTA);
//
//	Vector3 offset = XMVector3TransformCoord(focusOffset, rotMatrix);
//	view  = XMMatrixLookAtLH(this->Position(), target->Position() + offset, Vector3(0,1,0));
//
//	invView = XMMatrixInverse(nullptr, view);
//	viewBuffer->Set(view, invView);
//
//	this->UpdateWorld();
//}
