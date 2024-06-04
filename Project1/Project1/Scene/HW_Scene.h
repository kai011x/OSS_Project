#pragma once

class HW_Scene : public Scene
{
public:
	HW_Scene();
	~HW_Scene();

	// Scene��(��) ���� ��ӵ�
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
	int anime_num = 0;	// r���� ���ϸ� 0 ,g���� ���ϸ� 1 , b���� ���ϸ� 2
	bool hit = false;	// true�� �ִϸ��̼� �����ְ� �̵�

	float hit_Time = 0.0f;	// 1�ʵڸ� �ٽ� ������ �������� ����
	float scale_stack = 0;	// stack�� 100�̸� ���
	int cur_coin_num  = 100;
};
