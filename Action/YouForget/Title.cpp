#include "pch.h"

Title::Title(const SceneType& _nowScene)
	:SceneBase(_nowScene)
{
	// mClearEndFlagをtrueにする
	ResultBase::mClearEndFlag = true;

	// タイトル画像の生成
	mFullPicture = new FullPicture("Assets/UI/Title/TitleB.png");
	
	// mGetNumberを空にする
	ItemBase::mGetNumber.clear();
}

Title::~Title()
{
	// 現在のシーンで生成したオブジェクトを全て削除
	GAME_OBJECT_MANAGER->RemoveGameObjects(SceneType::eTitle);
}

void Title::Input(const InputState& _state)
{
	// フェード更新中じゃないとき
	// コントローラーのAボタン、または、スペースキーが押された瞬間
	if (!Fade::mFadeFlag && _state.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_A) == 1 ||
		!Fade::mFadeFlag && _state.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::Released)
	{

		// シーン遷移フラグをtrueにする
		mGameSceneFlag = true;
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
		//return new ThirdStage(Scene::third);
		//return new Result(Scene::result);
	}

	return mIsSceneType;
}