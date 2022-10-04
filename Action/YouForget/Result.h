#pragma once

class Result :public ResultBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_nowScene 現在のシーン
	*/
	Result(const SceneType& _nowScene);

	/*
	@fn	デストラクタ
	*/
	~Result();

	/*
	@fn	タイトルシーン時に毎フレーム更新処理をする
	*/
	SceneBase* update() override;

	/*
	@fn	タイトルシーン時に毎フレーム入力処理をする
	*/
	void Input(const InputState& _inputState)override;
};
