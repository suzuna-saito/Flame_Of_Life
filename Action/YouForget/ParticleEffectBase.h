#pragma once

/*
* エフェクトの基底クラス
*/
class ParticleEffectBase : public GameObject
{
public:
	// パーティクルの状態
	enum class ParticleState :unsigned char
	{
		eParticleActive,	// アクティブ
		eParticleDisable,	// 無効にする
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner">アタッチするゲームオブジェクトのポインタ</param>
	/// <param name="_billFlag">カメラの方向を向くかどうか true:向く</param>
	ParticleEffectBase(class GameObject* _owner, bool _billFlag = false);
	// デストラクタ
	virtual ~ParticleEffectBase() {};

protected:
	class ParticleComponent* mParticle;	// パーティクルの描画クラス
	class GameObject* mOwner;			// アタッチしたオブジェクトのポインタ
	
	Vector3 mAngle;						// 回転値
	float mFloatScale;					// 単体スケール値（float）
public:
	// 画像を描画するかしないかセットする true:描画する
	void SetThisVisible(bool _flag) { mParticle->SetVisible(_flag); }
};