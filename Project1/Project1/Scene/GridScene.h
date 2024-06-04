#pragma once

class GridScene : public Scene
{
public:
	GridScene();
	~GridScene();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUIRender() override;
	virtual void InfoRender() override;
	virtual void UpgradeButton() override;

private:
	Grid* grid;

	

};