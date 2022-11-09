#include "pch.h"

SecondResult::SecondResult(const SceneType& _nowScene)
	:ResultBase(_nowScene)
{
	// パズルの土台UIを生成
	new PuzzleUI("Assets/UI/SecondResult/SecondResultBase.png", UIBase::UIType::ePuzzleBase);

	// アイテムと画像データを関連付け	
	mPuzzlePieceDatas[PuzzlePiece::PieceNum::eOne] = "Assets/UI/SecondResult/Puzzles_1.png";
	mPuzzlePieceDatas[PuzzlePiece::PieceNum::eTwo] = "Assets/UI/SecondResult/Puzzles_2.png";
	mPuzzlePieceDatas[PuzzlePiece::PieceNum::eThree] = "Assets/UI/SecondResult/Puzzles_3.png";

	// どのパズルピースを取得したか検索、格納
	Search();
	// 全てのパズルピースを回収出来てたら
	if (Collected())
	{
		// 回収出来た用のテキスト画像を追加格納
		StoresData("Assets/UI/SecondResult/Word_1.png", UIBase::UIType::eText);
		StoresData("Assets/UI/SecondResult/Word_2.png", UIBase::UIType::eText);
	}
}

SecondResult::~SecondResult()
{
	// 現在のシーンで生成したオブジェクトを全て削除
	GAME_OBJECT_MANAGER->RemoveGameObjects(SceneType::eSecondResult);
}

void SecondResult::Input(const InputState& _state)
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

SceneBase::SceneType SecondResult::update()
{
	// mGameSceneFlagがtrueだったら
	if (mGameSceneFlag)
	{
		// 次のシーンのタイプを返す
		return SceneType::eThird;
	}

	// mReturnTitleFlagがtrueだったら
	if (mReturnTitleFlag)
	{
		// タイトルシーンタイプを返す
		return SceneType::eTitle;
	}

	return mIsSceneType;
}