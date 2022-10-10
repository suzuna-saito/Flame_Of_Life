#pragma once

/*
* ゴール場所に描画するエフェクト
*/
class GoalEffect : public ParticleEffectBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner">アタッチするゲームオブジェクトのポインタ</param>
	GoalEffect(class GameObject* _owner);
	// デストラクタ
	~GoalEffect() {};

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="_deltaTime">最後のフレームを完了するのに要した時間</param>
	void UpdateGameObject(float _deltaTime)override;

private:
	const float MAddAngleY;	// 回転値の増加値
	const float MMInAlpha;	// α値の最低値
	float mAddScale;		// スケールの追加値
	float mAddAlpha;		// アルファ値の減少値
};