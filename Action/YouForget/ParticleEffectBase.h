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

	// コンストラクタ
	ParticleEffectBase();
	// デストラクタ
	virtual ~ParticleEffectBase() {};

	/*
	@fn		派生クラスの更新関数を呼び座標に移動量を足し続ける
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

protected:

	/*
	@fn 生存時間をカウントダウンする関数。派生クラスで更新関数を決定した場合そこに追加すること。
	*/
	void LifeCountDown();

	//パーティクルの描画クラス
	ParticleComponent* mParticle;
	// 回転
	Vector3             mAngle;
	//生存時間
	int					mLifeCount;

	class GameObject* mOwner;	// アタッチしたオブジェクトのポインタ
public:
	/*
	@param _flag 反転を行うか
	*/
	void SetReverve(float _flag);

	// 画像を描画するかしないかセットする true:描画する
	void SetThisVisible(bool _flag) { mParticle->SetVisible(_flag); }
};