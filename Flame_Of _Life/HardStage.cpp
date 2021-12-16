/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_nowScene 現在のシーン
*/
HardStage::HardStage(const Scene& _nowScene)
	:SceneBase()
{
	SetScene(_nowScene);

	mMapCreate = new MapCreate();

	if (!mMapCreate->OpenFile())
	{
		// 床の生成
		mMapCreate->CreateGround();
		// プレイヤーの生成
		mMapCreate->CreatePlayer();
		// ろうそくの生成
		mMapCreate->CreateCandle();
		// アイテムの生成
		mMapCreate->CreateItem();
	}

	// カウントアップ
	new CountUp(_nowScene);

	new ItemCount(_nowScene);
}

/*
@fn	デストラクタ
*/
HardStage::~HardStage()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(Scene::hard);

	delete mMapCreate;
}


void HardStage::Input(const InputState& _state)
{
	// 当たり判定表示モードの切り替え
	if (_state.m_keyboard.GetKeyState(SDL_SCANCODE_0) == ButtonState::Pressed)
	{
		PHYSICS->ToggleDebugMode();
	}
}

/*
@fn	現在のシーン時に毎フレーム更新処理をする
*/
SceneBase* HardStage::update()
{
	// プレイヤーがろうそくにたどり着いたら
	if (Candle::mCandleCount == 2)
	{
		// 遷移フラグをtrueにする
		mGameSceneFlag = true;
	}

	// 遷移フラグがtrueだったら
	if (mGameSceneFlag)
	{
		// カウントを減らす
		mNextSceneCount--;
		// カウントが0以下になったら
		if (mNextSceneCount <= 0)
		{
			return new Result(Scene::result);
		}
	}

	CountUp::SetCountStartFlag(true);

	return this;
}
