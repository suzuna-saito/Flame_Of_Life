#pragma once

class SecondResult :public ResultBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_nowScene 現在のシーン
	*/
	SecondResult(const Scene& _nowScene);

	/*
	@fn	デストラクタ
	*/
	~SecondResult();

	/*
	@fn	タイトルシーン時に毎フレーム更新処理をする
	*/
	SceneBase* update() override;

	/*
	@fn	タイトルシーン時に毎フレーム入力処理をする
	*/
	void Input(const InputState& _inputState)override;
};
