#pragma once

/*
* ストーリーを進めるためのボタンUIの更新
*/
class AButtonUI :public UIBase
{
public:
	// コンストラクタ
	AButtonUI();
	// デストラクタ
	~AButtonUI() {};

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="_deltaTime">最後のフレームを完了するのに要した時間</param>
	void UpdateGameObject(float _deltaTime)override;

private:
	float mAddScale;	// スケールの増加値
};