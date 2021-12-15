/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_nowScene 現在のシーン
*/
NormalStage::NormalStage(const Scene& _nowScene)
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
	}

	// カウントアップ
	new CountUp(_nowScene);
}

/*
@fn	デストラクタ
*/
NormalStage::~NormalStage()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(Scene::normal);

	delete mMapCreate;
}


void NormalStage::Input(const InputState& _state)
{
	// 当たり判定表示モードの切り替え
	if (_state.m_keyboard.GetKeyState(SDL_SCANCODE_0) == 1)
	{
		PHYSICS->ToggleDebugMode();
	}
}

/*
@fn	現在のシーン時に毎フレーム更新処理をする
*/
SceneBase* NormalStage::update()
{
	if (Candle::mCandleCount == 3)
	{
		return new HardStage(Scene::hard);
	}

	CountUp::SetCountStartFlag(true);

	return this;
}
