/*
@brief	プリプロセッサ
*/
#pragma once

class ThirdStage : public SceneBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_nowScene 現在のシーン
	*/
	ThirdStage(const Scene& _nowScene);

	/*
	@fn	デストラクタ
	*/
	~ThirdStage();

	void Input(const InputState& state)override;

	/*
	@fn	現在のシーン時に毎フレーム更新処理をする
	*/
	SceneBase* update() override;

private:

};

