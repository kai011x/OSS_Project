#pragma once

class HW_Scene : public Scene
{
public:
	HW_Scene();
	~HW_Scene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUIRender() override;
	virtual void InfoRender() override;
	virtual void UpgradeButton() override;


private:
	Anime_2D* anime_r;
	Anime_2D* anime_g;
	Anime_2D* anime_b;

	Anime_2D* Win_anime;

	Anime_2D* you_Win;
	Anime_2D* you_Die;


	int hp = 5;
	int anime_num = 0;	// r에게 당하면 0 ,g에게 당하면 1 , b에게 당하면 2
	bool hit = false;	// true면 애니메이션 보여주고 이동

	float hit_Time = 0.0f;	// 1초뒤면 다시 리스폰 지역으로 갈것
	float scale_stack = 0;	// stack이 100이면 충분
	int cur_coin_num  = 100;
};
