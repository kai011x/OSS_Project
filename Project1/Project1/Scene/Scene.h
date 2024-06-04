#pragma once

class Scene
{
public:
	virtual ~Scene() = default;

	virtual void Update() = 0;

	virtual void PreRender() = 0;	//Render Target
	virtual void Render() = 0;
	virtual void PostRender() = 0;	
	virtual void GUIRender() = 0;	// ImGui
	virtual void InfoRender() = 0;	// 정보 알려주는 용도
	virtual void UpgradeButton() = 0;

	virtual void Start() {}
	virtual void End() {}

};