#include "pch.h"

FirstStage::FirstStage(const SceneType& _nowScene)
	:SceneBase(_nowScene)
{
	// マップの生成
	mMapCreate = new MapCreate(_nowScene);
	// ThirdStage用のファイルが開けたら
	if (!mMapCreate->OpenFile())
	{
		// プレイヤーの生成
		mMapCreate->CreatePlayer();
		// 床の生成
		mMapCreate->CreateGround();
	}
}

FirstStage::~FirstStage()
{
	// 現在のシーンで生成したオブジェクトを全て削除
	GAME_OBJECT_MANAGER->RemoveGameObjects(SceneType::eFirst);
}

void FirstStage::Input(const InputState& _state)
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

SceneBase::SceneType FirstStage::update()
{
	// mGameSceneFlagがtrueかつ、フェード中じゃなければ
	if (mGameSceneFlag && !Fade::mFadeFlag)
	{
		// 次のシーンのタイプを返す
		return SceneType::eFirstResult;
	}
	// mReturnTitleFlagがtrueだったら
	if (mReturnTitleFlag)
	{
		// タイトルシーンタイプを返す
		return SceneType::eTitle;
	}

	// プレイヤーがゴールにたどり着いた時、フェードの更新をしていなかったら
	if (!Fade::mFadeFlag)
	{
		// シーン遷移フラグをtrueにする
		mGameSceneFlag = true;
		// 黒いフェードアウトをさせる
		//mFade->SetFade(Color::Black, Fade::FadeType::eOut);
	}

	return mIsSceneType;
}