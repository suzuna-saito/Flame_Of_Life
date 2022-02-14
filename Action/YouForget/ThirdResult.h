#pragma once

class ThirdResult :public ResultBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_nowScene 現在のシーン
	*/
	ThirdResult(const Scene& _nowScene);

	/*
	@fn	デストラクタ
	*/
	~ThirdResult();

	/*
	@fn	タイトルシーン時に毎フレーム更新処理をする
	*/
	SceneBase* update() override;

	/*
	@fn	タイトルシーン時に毎フレーム入力処理をする
	*/
	void Input(const InputState& _inputState)override;
};
