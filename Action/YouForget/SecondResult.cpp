/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_nowScene 現在のシーン
*/
SecondResult::SecondResult(const Scene& _nowScene)
	:ResultBase(_nowScene)
{
	// マップをつかってアイテムと説明画像を関連付け	
	mItemDescription[ItemNum::one] = "Assets/UI/FarstThree.png";
	mItemDescription[ItemNum::two] = "Assets/UI/FarstTwo.png";
	mItemDescription[ItemNum::three] = "Assets/UI/FarstOne.png";

	// どのアイテムを取っているか検索
	mSearch();
}

/*
@fn	デストラクタ
*/
SecondResult::~SecondResult()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(Scene::secondResult);
}

void SecondResult::Input(const InputState& _state)
{
	if (_state.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == ButtonState::Released ||
		_state.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::Released)
	{
		mDrawUpdate();
	}
}


/*
@fn	現在のシーン時に毎フレーム更新処理をする
*/
SceneBase* SecondResult::update()
{
	mResultUpdate();

	if (mGameSceneFlag)
	{
		return new ThirdStage(Scene::third);
	}

	return this;
}