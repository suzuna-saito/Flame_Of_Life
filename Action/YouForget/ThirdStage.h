#pragma once

/*
* ThirdStageの更新
*/
class ThirdStage : public SceneBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_nowScene">現在のシーンタイプ</param>
	ThirdStage(const SceneType& _nowScene);
	// デストラクタ
	~ThirdStage();

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