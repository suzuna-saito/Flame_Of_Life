/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_nowScene 現在のシーン
*/
Stage01::Stage01(const Scene& _nowScene)
	:SceneBase()
{
	SetScene(_nowScene);

	mMapCreate = new MapCreate();

	if (!mMapCreate->OpenFile())
	{
		// 床の生成
		mMapCreate->CreateGround();
		// プレイヤーの生成
		mMapCreate->CreatePlayer();
		// ろうそくの生成
		mMapCreate->CreateCandle();
	}
}

/*
@fn	デストラクタ
*/
Stage01::~Stage01()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(stage01);
}


void Stage01::Input(const InputState& _state)
{
}

/*
@fn	現在のシーン時に毎フレーム更新処理をする
*/
SceneBase* Stage01::update()
{

	return this;
}
