/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_nowScene 現在のシーン
*/
FirstResult::FirstResult(const SceneType& _nowScene)
	:ResultBase(_nowScene)
{
	mPuzzleUI = new PuzzleUI("Assets/UI/FirstResult/FirstResultBase.png", UIBase::UIType::ePuzzleBase);

	// アイテムと画像データを関連付け	
	mPuzzlePieces[ItemNum::one] = "Assets/UI/FirstResult/Puzzles_1.png";
	mPuzzlePieces[ItemNum::two] = "Assets/UI/FirstResult/Puzzles_2.png";
	mPuzzlePieces[ItemNum::three] = "Assets/UI/FirstResult/Puzzles_3.png";

	// どのパズルピースを取得したか検索
	mSearch();
}

/*
@fn	デストラクタ
*/
FirstResult::~FirstResult()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(SceneType::eFirstResult);
}

void FirstResult::Input(const InputState& _state)
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
SceneBase* FirstResult::update()
{
	if (mGameSceneFlag)
	{
		return new SecondStage(SceneType::eSecond);
		//return new SecondResult(SceneType::eSecondResult);

		//return new Result(Scene::gameClear);
	}

	if (mReturnTitleFlag)
	{
		return new Title(SceneType::eTitle);
	}

	mResultUpdate();

	return this;
}