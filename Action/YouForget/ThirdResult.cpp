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
	mPuzzlePieceDatas[ItemNum::one] = "Assets/UI/ThirdResult/Puzzles_1.png";
	mPuzzlePieceDatas[ItemNum::two] = "Assets/UI/ThirdResult/Puzzles_2.png";
	mPuzzlePieceDatas[ItemNum::three] = "Assets/UI/ThirdResult/Puzzles_3.png";

	// どのアイテムを取っているか検索
	Search();
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
}


/*
@fn	現在のシーン時に毎フレーム更新処理をする
*/
SceneBase* ThirdResult::update()
{
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