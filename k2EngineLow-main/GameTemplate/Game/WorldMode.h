#pragma once
#include "sound/SoundSource.h"




class Loading;


class WorldMode:public IGameObject
{
public:
	WorldMode();
	~WorldMode();
	bool Start();
	void Update();
	void Render(RenderContext&rc);

private:
	Vector4 m_SelectSpriteColor = { 1.0f,1.0f,1.0f,0.0f };
	Vector4 m_NonSelectSpriteColor = { 1.0f,1.0f,1.0f,0.0f };

	Vector4 m_WindowSpriteColor = { 1.0f,1.0f,1.0f,0.0f };

	Vector3 m_WindowSpritePosition = { 0.0f,-50.0f,0.0f };

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
	SpriteRender WorldRaceSprite;			//レース
	SpriteRender WorldRaceSelectSprite;		//レースセレクト中
	SpriteRender OptionSprite;				//設定
	SpriteRender OptionSelectSprite;		//設定セレクト中
	SpriteRender SelectArrowSprite;			//矢印
	SpriteRender MyCarSprite;				//今乗っている車の名前
	SpriteRender TestSprite;				//テスト用のスプライト
	SpriteRender ErrorWindowSprite;				//エラー時のポップアップウィンドウ
	SpriteRender WindowBottonOKSprite;			//ウィンドウのOKボタン

	SpriteRender BlackOut;

	Loading* m_loading;
	SoundSource* BGM;
	SoundSource* CursorSE;
	SoundSource* DecisionSE;
						

	Vector3 SelectArrowPosition = Vector3::Zero;

	Vector4 SelectAppealColor = { 1.0f,1.0f,1.0f,0.0f };
	Vector4 m_FadeColor = { 1.0f,1.0f,1.0f,1.0f };

	int SelectState = 0; //0:MyGarage 1:WorldRace 2:License 3:CarDealer 4:Tuning 5:Maintenance
	int ErrorWindowFlag = 0;//0:非表示 1:表示遷移 2:表示中 3:非表示遷移
	int FadeSate = -1;
	int WindowCount = 0;
	int Count = 0;		//セレクトチカチカの時間
	int SelectDirection = 1;
	int SelectFlag[6] = { 0,0,0,0,0,0 };
	int FadeCount = 0;
};

