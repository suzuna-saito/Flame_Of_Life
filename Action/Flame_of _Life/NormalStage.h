/*
@brief	プリプロセッサ
*/
#pragma once

class NormalStage : public SceneBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_nowScene 現在のシーン
	*/
	NormalStage(const Scene& _nowScene);

	/*
	@fn	デストラクタ
	*/
	~NormalStage();

	void Input(const InputState& state)override;

	/*
	@fn	現在のシーン時に毎フレーム更新処理をする
	*/
	SceneBase* update() override;

private:

};

