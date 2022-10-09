#include "pch.h"

LastResult::LastResult(const SceneType& _nowScene)
	:ResultBase(_nowScene)
{
	if (mClearEndFlag)
	{
		mFullPicture = new FullPicture("Assets/UI/EndResult/Clear_1.png");
	}
	else
	{
		mFullPicture = new FullPicture("Assets/UI/EndResult/Clear_4.png");
	}
}

LastResult::~LastResult()
{
	// 現在のシーンで生成したオブジェクトを全て削除
	GAME_OBJECT_MANAGER->RemoveGameObjects(SceneType::eLastResult);
}

void LastResult::Input(const InputState& _state)
{
	// コントローラーのAボタン、または、スペースキーが押された瞬間
	if (_state.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == ButtonState::Released ||
		_state.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::Released)
	{
		// 格納されている画像を描画
		// 全て描画されていた時はシーン遷移フラグがtrueになる
		mGameSceneFlag = mDrawUpdate();
	}
	// タイトルシーン以外でコントローラーのスタートボタン、または、Bキーが押された瞬間
	if (_state.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_START) == 1 ||
		_state.m_keyboard.GetKeyState(SDL_SCANCODE_B) == ButtonState::Released)
	{
		// タイトル遷移フラグをtrueにする
		mReturnTitleFlag = true;
	}
}

SceneBase::SceneType LastResult::update()
{
	// mGameSceneFlagがtrueだったら
	if (mGameSceneFlag)
	{
		// 次のシーンのタイプを返す
		return SceneType::eTitle;
	}

	return mIsSceneType;
}