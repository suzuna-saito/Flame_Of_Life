#pragma once

/*
* ゲームクリアかゲームオーバーだった時の更新を行うクラス
*/
class LastResult :public ResultBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_nowScene 現在のシーン
	*/
	LastResult(const SceneType& _nowScene);

	/*
	@fn	デストラクタ
	*/
	~LastResult();

	/*
	@fn	タイトルシーン時に毎フレーム更新処理をする
	*/
	SceneBase* update() override;

	/*
	@fn	タイトルシーン時に毎フレーム入力処理をする
	*/
	void Input(const InputState& _inputState)override;
};
