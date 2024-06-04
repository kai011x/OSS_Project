#pragma once

class HW_Basic_Character : public Transform
{
public:
	HW_Basic_Character(string file);
	~HW_Basic_Character();

	virtual void Update() {}
	virtual void Render() {}
	virtual void PostRender() {}
	virtual void InfoRender() {}

public:
	virtual void Set_respawn_Pos(Vector3 pos){}
	virtual void Hit(UINT damage) {}
	virtual bool Check_Die() { return false; }


	Collider* GetCollider() { return collider; }
protected:
	void Set_Tags(string name);

	void Update_Basis();
	void Render_Basis();


	Collider* collider;

	bool Show_Collider = true;

	float delay_mouse_point_check = 0.0f;
	
};
