#pragma once
	

class Transform
{
public:
	Transform();
	~Transform();

	void UpdateWorld();
	void GUIRender();
	void SetParent(Transform* transform) { 
		parent = &transform->GetWorld();
		parentTransform = transform; 
	}
	void SetParent(Matrix* matrix) { parent = matrix; }
	void Delete_Parent() { parent = nullptr; parentTransform = nullptr; }

	Matrix& GetWorld() { return world; }

	Vector3 Forward();
	Vector3 Right();
	Vector3 Up();

	void Save();
	void Load();

	Vector3 GlobalPos() { return globalPosition; }
	Vector3 GlobalScale() { return globalScale; }

	Vector3& Position() { return local_Position; }
	Vector3& Rotation() { return local_Rotation; }

	Vector3& Scale() { return local_Scale; }
	
	string& Tag() { return tag; }
	void SetActive(bool isActive) { this->isActive = isActive; }
	bool ActiveSelf() { return isActive; }
	bool Active();

	Vector3& GetPivotS() { return pivotS; }
private:
	string tag = "Untagged";

	bool isActive = true;

	Vector3 local_Position;
	Vector3 local_Rotation;
	Vector3 local_Scale;

	Vector3 globalPosition;
	Vector3 globalRotation;
	Vector3 globalScale;

protected:
	Vector3 pivotS;	//회전-크기 변환 축
	Vector3 pivotR;

	Matrix world;

	Transform* parentTransform;
	Matrix* parent;

};