/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_nowScene 現在のシーン
*/
ThirdResult::ThirdResult(const SceneType& _nowScene)
	:ResultBase(_nowScene)
{
	mFullPicture = new FullPicture("Assets/UI/ThirdResult/ThirdResultBase.png");

	// マップをつかってアイテムと説明画像を関連付け	
	mPuzzlePieces[ItemNum::one] = "Assets/UI/ThirdResult/Puzzles_1.png";
	mPuzzlePieces[ItemNum::two] = "Assets/UI/ThirdResult/Puzzles_2.png";
	mPuzzlePieces[ItemNum::three] = "Assets/UI/ThirdResult/Puzzles_3.png";

	// どのアイテムを取っているか検索
	mSearch();
}

/*
@fn	デストラクタ
*/
ThirdResult::~ThirdResult()
{
	delete mFullPicture;
	GAME_OBJECT_MANAGER->RemoveGameObjects(SceneType::eThirdResult);
}

void ThirdResult::Input(const InputState& _state)
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
SceneBase* ThirdResult::update()
{
	mResultUpdate();

	if (mGameSceneFlag)
	{
		return new LastResult(SceneType::eGameClear);
	}

	if (mReturnTitleFlag)
	{
		return new Title(SceneType::eTitle);
	}

	return this;
}