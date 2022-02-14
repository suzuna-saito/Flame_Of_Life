/*
@file ParticleEffectBase.h
@brief 一定時間で消える、主にエフェクトの基底クラスとして使用されるクラス
*/

/*
@brief	プリプロセッサ
*/
#pragma once


/*
@enum	パーティクルの状態
*/
enum class ParticleState :unsigned char
{
	//アクティブ
	PARTICLE_ACTIVE,
	//無効にする
	PARTICLE_DISABLE,
};

class ParticleEffectBase : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_pos エフェクトの生成場所
	@param	_vel エフェクトの速度
	@param	_lifeCount エフェクトの生存時間
	@param	_particleFileName 画像へのアドレス
	@param	_objectTag アタッチしたゲームオブジェクトのタグ
	@param	_sceneTag シーンのタグ
	@param	_scale 画像の拡大サイズ
	*/
	ParticleEffectBase(const Vector3& _pos, const Vector3& _vel, const int& _lifeCount, const std::string& _particleFileName, SceneBase::Scene _sceneTag, const Tag& _objectTag , bool _billFlag ,const float& _scale = 10);

	/*
	@fn	デストラクタ
	*/
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

	//生存時間
	int					mLifeCount;

	//アルファ値
	float				mAlpha;
	//大きさ
	float				mScale;
	//加速度
	float				mSpeed;

public:

	/*
	@param _flag 反転を行うか
	*/
	void SetReverve(float _flag);
};
