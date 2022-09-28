/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_nowScene 現在のシーン
*/
ThirdStage::ThirdStage(const Scene& _nowScene)
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
ThirdStage::~ThirdStage()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(Scene::third);

	delete mMapCreate;
	delete mSprite;
}


void ThirdStage::Input(const InputState& _state)
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
SceneBase* ThirdStage::update()
{
	// プレイヤーがろうそくにたどり着いたら
	if (Candle::mGoalFlag)
	{
		
		return new ThirdResult(Scene::thirdResult);
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
