#pragma once

/*
* ストーリーを進めるためのボタンUIの更新、描画するクラス
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
	const float mMaxScale;	// スケールの最大値
	const float mMinScale;	// スケールの最小値
	float mAddScale;		// スケールの増加値
};