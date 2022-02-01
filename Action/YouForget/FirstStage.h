/*
@brief	プリプロセッサ
*/
#pragma once

class FirstStage : public SceneBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_nowScene 現在のシーン
	*/
	FirstStage(const Scene& _nowScene);

	/*
	@fn	デストラクタ
	*/
	~FirstStage();

	void Input(const InputState& state)override;

	/*
	@fn	現在のシーン時に毎フレーム更新処理をする
	*/
	SceneBase* update() override;

private:

};

