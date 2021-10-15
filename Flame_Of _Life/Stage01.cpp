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
	GAME_OBJECT_MANAGER->RemoveGameObjects(stage01);
}

/*
@fn	デストラクタ
*/
Stage01::~Stage01()
{
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
