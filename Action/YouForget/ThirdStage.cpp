/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_nowScene 現在のシーン
*/
ThirdStage::ThirdStage(const Scene& _nowScene)
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

}

/*
@fn	デストラクタ
*/
ThirdStage::~ThirdStage()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(Scene::third);

	delete mMapCreate;
}


void ThirdStage::Input(const InputState& _state)
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
SceneBase* ThirdStage::update()
{
	// プレイヤーがろうそくにたどり着いたら
	if (Candle::mCandleCount == 1)
	{
		// 遷移フラグをtrueにする
		mGameSceneFlag = true;
	}

	// 遷移フラグがtrueだったら
	if (mGameSceneFlag)
	{
		//return new Result(Scene::result);

		//// カウントを減らす
		//mNextSceneCount--;
		//// カウントが0以下になったら
		//if (mNextSceneCount <= 0)
		//{
		//	return new Result(Scene::result);
		//}
	}

	return this;
}
