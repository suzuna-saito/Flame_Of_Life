/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_nowScene 現在のシーン
*/
FirstStage::FirstStage(const Scene& _nowScene)
	:SceneBase()
{
	SetScene(_nowScene);

	mMapCreate = new MapCreate();

	if (!mMapCreate->OpenFile())
	{
		// プレイヤーの生成
		mMapCreate->CreatePlayer();
		// 背景の生成
		mMapCreate->CreateBackGround();
		// 床の生成
		mMapCreate->CreateGround();
		// スイッチの生成
		mMapCreate->CreateSwitch();
		// ろうそくの生成
		mMapCreate->CreateCandle();
		// アイテムの生成
		mMapCreate->CreateItem();
	}

	mSprite = new Sprite("Assets/UI/Description.png");
}

/*
@fn	デストラクタ
*/
FirstStage::~FirstStage()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(Scene::first);

	delete mSprite;
	delete mMapCreate;
}


void FirstStage::Input(const InputState& _state)
{
	// 当たり判定表示モードの切り替え
	if (_state.m_keyboard.GetKeyState(SDL_SCANCODE_0) == ButtonState::Pressed)
	{
		PHYSICS->ToggleDebugMode();
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
SceneBase* FirstStage::update()
{
	if (Candle::mCandleCount == 1)
	{
		//return new SecondStage(Scene::second);
		return new FirstResult(Scene::firstResult);
	}

	if (mReturnTitleFlag)
	{
		return new Title(Scene::title);
	}


	// @@@
	if (!Player::mMoveFlag)
	{
		mSprite->SetThisVisible(true);
	}
	else
	{
		mSprite->SetThisVisible(false);
	}

	return this;
}
