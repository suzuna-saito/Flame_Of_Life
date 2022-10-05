/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_nowScene 現在のシーン
*/
Title::Title(const SceneType& _nowScene)
	:SceneBase()
{
	mIsScene = _nowScene;

	// タイトル画像
	mFullPicture = new FullPicture("Assets/UI/Title/TitleB.png");

	ResultBase::mTrueEndFlag = true;

	// 取得したアイテムの中にデータが入っていれば
	if (ItemBase::mGetNumber.size() != 0)
	{
		ItemBase::mGetNumber.clear();
	}
}

/*
@fn	デストラクタ
*/
Title::~Title()
{
	delete mFullPicture;
	GAME_OBJECT_MANAGER->RemoveGameObjects(SceneType::eTitle);
}

void Title::Input(const InputState& _state)
{
	if (_state.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_A) == 1 ||
		_state.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::Released)
	{
		mGameSceneFlag = true;
	}

}

/*
@fn	現在のシーン時に毎フレーム更新処理をする
*/
SceneBase* Title::update()
{
	if (mGameSceneFlag)
	{
		return new FirstStage(SceneType::eFirst);
		//return new Tutorial(Scene::tutorial);
		//return new SecondStage(Scene::second);
		//return new ThirdStage(Scene::third);
		//return new Result(Scene::result);
	}

	return this;
}