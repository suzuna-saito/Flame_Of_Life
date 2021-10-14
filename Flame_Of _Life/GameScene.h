/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/
#include "SceneBase.h"

class GameScene : public SceneBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_nowScene 現在のシーン
	*/
	GameScene(const Scene& _nowScene);

	/*
	@fn	デストラクタ
	*/
	~GameScene();

	void Input(const InputState& state)override;

	/*
	@fn	現在のシーン時に毎フレーム更新処理をする
	*/
	SceneBase* update() override;

private:

};
