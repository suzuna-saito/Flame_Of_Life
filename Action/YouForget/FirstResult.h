#pragma once

/*
* FirstStageのリザルトクラス
*/
class FirstResult : public ResultBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_nowScene">現在のシーンタイプ</param>
	FirstResult(const SceneType& _nowScene);
	// デストラクタ
	~FirstResult();

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
