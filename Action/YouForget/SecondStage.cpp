/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_nowScene 現在のシーン
*/
SecondStage::SecondStage(const SceneType& _nowScene)
	:SceneBase(_nowScene)
{
	mIsScene = _nowScene;

	mMapCreate = new MapCreate();

	if (!mMapCreate->OpenFile())
	{
		// プレイヤーの生成
		mMapCreate->CreatePlayer();
		// 背景の生成
		mMapCreate->CreateBackGround();
		// 床の生成
		mMapCreate->CreateGround();
		// スイッチの生成
		mMapCreate->CreateSwitch();
		// ろうそくの生成
		mMapCreate->CreateCandle();
		// アイテムの生成
		mMapCreate->CreateItem();
	}

	mFullPicture = new FullPicture("Assets/UI/Description.png");
}

/*
@fn	デストラクタ
*/
SecondStage::~SecondStage()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(SceneType::eSecond);

	delete mMapCreate;
}


void SecondStage::Input(const InputState& _state)
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
SceneBase* SecondStage::update()
{
	if (GoalObj::mGoalFlag)
	{
		return new SecondResult(SceneType::eSecondResult);
	}

	if (mReturnTitleFlag)
	{
		return new Title(SceneType::eTitle);
	}


	// @@@
	if (!Player::mMoveFlag)
	{
		mFullPicture->SetThisVisible(true);
	}
	else
	{
		mFullPicture->SetThisVisible(false);
	}
	return this;
}
