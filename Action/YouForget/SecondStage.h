/*
@brief	プリプロセッサ
*/
#pragma once

class SecondStage : public SceneBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_nowScene 現在のシーン
	*/
	SecondStage(const SceneType& _nowScene);

	/*
	@fn	デストラクタ
	*/
	~SecondStage();

	void Input(const InputState& state)override;

	/*
	@fn	現在のシーン時に毎フレーム更新処理をする
	*/
	SceneBase* update() override;

private:

};

