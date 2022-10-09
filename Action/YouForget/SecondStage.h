#pragma once

/*
* SecondStageの更新
*/
class SecondStage : public SceneBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_nowScene">現在のシーンタイプ</param>
	SecondStage(const SceneType& _nowScene);
	// デストラクタ
	~SecondStage();

	/// <summary>
	/// 入力処理
	/// </summary>
	/// <param name="_inputState">入力状態</param>
	void Input(const InputState& _inputState)override;
	/// <summary>
	/// 更新処理
	/// </summary>
	/// <returns>次のシーンのタイプ</returns>
	SceneType update() override;
};