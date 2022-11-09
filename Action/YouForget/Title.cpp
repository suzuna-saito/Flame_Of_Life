#include "pch.h"

Title::Title(const SceneType& _nowScene)
	:SceneBase(_nowScene)
{
	// mClearEndFlagをtrueにする
	ResultBase::mClearEndFlag = true;
	// 取得したピースの状態を空にする
	PuzzlePiece::mGetNumber.clear();

	// タイトル画像の生成
	mFullPicture = new FullPicture("Assets/UI/Title/Title.png");
}

Title::~Title()
{
	// 現在のシーンで生成したオブジェクトを全て削除
	GAME_OBJECT_MANAGER->RemoveGameObjects(SceneType::eTitle);
}

void Title::Input(const InputState& _state)
{
	// コントローラーのAボタン、または、スペースキーが押された瞬間
	if (_state.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_A) == 1 ||
		_state.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::Released)
	{
		// シーン遷移フラグをtrueにする
		mGameSceneFlag = true;
		// 黒いフェードアウトをさせる
		mFade->SetFade(Color::Black, Fade::FadeType::eOut);
	}
}

SceneBase::SceneType Title::update()
{
	// mGameSceneFlagがtrueかつ、フェード中じゃなければ
	if (mGameSceneFlag && !Fade::mFadeFlag)
	{
		// 次のシーンのタイプを返す
		return SceneType::eFirst;
		//return new FirstResult(SceneType::eFirstResult);
		//return new Tutorial(Scene::tutorial);
		//return new SecondStage(Scene::second);
		//return SceneType::eThirdResult;
		//return new Result(Scene::result);
	}

	return mIsSceneType;
}