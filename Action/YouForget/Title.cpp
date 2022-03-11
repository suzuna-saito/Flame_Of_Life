/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_nowScene 現在のシーン
*/
Title::Title(const Scene& _nowScene)
	:SceneBase()
{
	SetScene(_nowScene);

	// タイトル画像
	mSprite = new Sprite("Assets/UI/Title/TitleB.png");

	Candle::mCandleCount = 0;

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
	GAME_OBJECT_MANAGER->RemoveGameObjects(Scene::title);
	delete mSprite;
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
		return new FirstStage(Scene::first);
		//return new Tutorial(Scene::tutorial);
		//return new SecondStage(Scene::second);
		//return new ThirdStage(Scene::third);
		//return new Result(Scene::result);
	}

	return this;
}