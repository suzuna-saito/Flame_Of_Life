#include "pch.h"

SecondStage::SecondStage(const SceneType& _nowScene)
	:SceneBase(_nowScene)
{
	// マップの生成
	mMapCreate = new MapCreate(_nowScene);
	// SecondStage用のファイルが開けたら
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
}

SecondStage::~SecondStage()
{
	// 現在のシーンで生成したオブジェクトを全て削除
	GAME_OBJECT_MANAGER->RemoveGameObjects(SceneType::eSecond);
}


void SecondStage::Input(const InputState& _state)
{
	// @@@デバック用
	// 当たり判定表示モードの切り替え
	if (_state.m_keyboard.GetKeyState(SDL_SCANCODE_0) == ButtonState::Pressed)
	{
		PHYSICS->ToggleDebugMode();
	}
	// タイトルシーン以外でコントローラーのスタートボタン、または、Bキーが押された瞬間
	if (_state.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_START) == 1 ||
		_state.m_keyboard.GetKeyState(SDL_SCANCODE_B) == ButtonState::Released)
	{
		// タイトル遷移フラグをtrueにする
		mReturnTitleFlag = true;
	}
}

SceneBase* SecondStage::update()
{
	// プレイヤーがゴールにたどり着いたら
	if (GoalObj::mGoalFlag)
	{
		// 次のシーンのポインタを返す
		return new SecondResult(SceneType::eSecondResult);
	}

	// mReturnTitleFlagがtrueだったら
	if (mReturnTitleFlag)
	{
		// タイトルシーンのポインタを返す
		return new Title(SceneType::eTitle);
	}

	return this;
}
