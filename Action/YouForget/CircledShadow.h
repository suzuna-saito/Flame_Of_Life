#pragma once

/*
* オブジェクトの丸影エフェクト
*/
class CircledShadow : public ParticleEffectBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner">アタッチするゲームオブジェクトのポインタ</param>
	/// <param name="_color">丸影の色</param>
	CircledShadow(class GameObject* _owner, const Vector3 _color);
	// デストラクタ
	~CircledShadow() {};

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="_deltaTime">最後のフレームを完了するのに要した時間</param>
	void UpdateGameObject(float _deltaTime)override;

private:	
	const float MBaseZPos;		// 丸影のｚポジション(基盤)
	const float MMaxScale;		// 最大スケール値
	const float MInitOwnerAlpha;// アタッチしたオブジェクトの元々の透明度
	const float MMaxAlpha;		// 最大α値
	const float MAddAlpha;		// α値の増加値
	const float MSubAlpha;		// α値の減少値
};