/*
@brief	プリプロセッサ
*/
#pragma once

class Title : public SceneBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_nowScene 現在のシーン
	*/
	Title(const SceneType& _nowScene);

	/*
	@fn	デストラクタ
	*/
	~Title();

	/*
	@fn	タイトルシーン時に毎フレーム更新処理をする
	*/
	SceneBase* update() override;

	/*
	@fn	タイトルシーン時に毎フレーム入力処理をする
	*/
	void Input(const InputState& _inputState)override;

private:
};

