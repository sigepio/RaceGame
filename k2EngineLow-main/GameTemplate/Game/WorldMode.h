#pragma once
class RaceMenu;


class WorldMode:public IGameObject
{
public:
	WorldMode();
	~WorldMode();
	bool Start();
	void Update();
	void Render(RenderContext&rc);
private:
	
	SpriteRender BaseSprite;				//背景
	SpriteRender MyGarageSprite;			//ガレージ
	SpriteRender MyGarageSelectSprite;		//ガレージセレクト中
	SpriteRender CarDealerSprite;			//ディーラー
	SpriteRender CarDealerSelectSprite;		//ディーラーセレクト中
	SpriteRender TuningSprite;				//チューニング
	SpriteRender TuningSelectSprite;		//チューニングセレクト中
	SpriteRender MaintenanceSprite;			//メンテナンス
	SpriteRender MaintenanceSelectSprite;	//メンテナンスセレクト中
	SpriteRender LicenseSprite;				//ライセンス
	SpriteRender LicenseSelectSprite;		//ライセンスセレクト中
	SpriteRender WprldRaceSprite;			//レース
	SpriteRender WprldRaceSelectSprite;		//レースセレクト中
	SpriteRender OptionSprite;				//設定
	SpriteRender OptionSelectSprite;		//設定セレクト中
	SpriteRender SelectArrowSprite;			//矢印
	SpriteRender MyCarSprite;				//今乗っている車の名前
	SpriteRender TestSprite;				//テスト用のスプライト

	RaceMenu* m_racemenu;					

	Vector3 SelectArrowPosition = Vector3::Zero;

	Vector4 SelectAppealColor = { 1.0f,1.0f,1.0f,0.0f };

	int SelectState = 0; //0:MyGarage 1:WorldRace 2:License 3:CarDealer 4:Tuning 5:Maintenance


};

