#pragma once

/*
* SecondStageのリザルトクラス
*/
class SecondResult :public ResultBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_nowScene">現在のシーンタイプ</param>
	SecondResult(const SceneType& _nowScene);
	// デストラクタ
	~SecondResult();

	/// <summary>
	/// 入力処理
	/// </summary>
	/// <param name="_inputState">入力状態</param>
	void Input(const InputState& _inputState)override;
	/// <summary>
	/// 更新処理
	/// </summary>
	/// <returns></returns>
	SceneBase* update() override;
};