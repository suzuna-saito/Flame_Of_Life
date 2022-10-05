/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_nowScene 現在のシーン
*/
SecondResult::SecondResult(const SceneType& _nowScene)
	:ResultBase(_nowScene)
{
	mFullPicture = new FullPicture("Assets/UI/SecondResult/SecondResultBase.png");

	// マップをつかってアイテムと説明画像を関連付け	
	mItemDescription[ItemNum::one] = "Assets/UI/SecondResult/Puzzles_1.png";
	mItemDescription[ItemNum::two] = "Assets/UI/SecondResult/Puzzles_2.png";
	mItemDescription[ItemNum::three] = "Assets/UI/SecondResult/Puzzles_3.png";

	// どのアイテムを取っているか検索
	mSearch();
}

/*
@fn	デストラクタ
*/
SecondResult::~SecondResult()
{
	delete mFullPicture;

	GAME_OBJECT_MANAGER->RemoveGameObjects(SceneType::eSecondResult);
}

void SecondResult::Input(const InputState& _state)
{
	if (_state.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == ButtonState::Released ||
		_state.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::Released)
	{
		mDrawUpdate();
	}

	if (_state.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_START) == 1 ||
		_state.m_keyboard.GetKeyState(SDL_SCANCODE_B) == ButtonState::Released)
	{
		mReturnTitleFlag = true;
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
		return new ThirdStage(SceneType::eThird);
	}

	if (mReturnTitleFlag)
	{
		return new Title(SceneType::eTitle);
	}

	return this;
}