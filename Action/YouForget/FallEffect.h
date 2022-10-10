#pragma once

/*
* オブジェクトが落ちた時に描画するエフェクト
*/
class FallEffect : public ParticleEffectBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner">アタッチするゲームオブジェクトのポインタ</param>
	FallEffect(class GameObject* _owner);
	// デストラクタ
	~FallEffect() {};

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="_deltaTime">最後のフレームを完了するのに要した時間</param>
	void UpdateGameObject(float _deltaTime)override;

private:
	const float MBaseScale;	// スケール値(基盤)
	const float MAddScale;	// スケールの追加値
	const float MSubAlpha;	// アルファ値の減少値

	bool mTmpVisible;		// 更新処理の最後に描画していたかどうかを保存
};