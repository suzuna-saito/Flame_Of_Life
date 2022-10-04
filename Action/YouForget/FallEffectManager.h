#pragma once

/*
@brief プリプロセッサ
*/
#pragma once

/*
@brief 前方宣言
*/
class FallEffect;
class Player;

///*
//@brief デスエフェクトの方向
//*/
//enum DirectionDeathEffect
//{
//	eLeftDeath = 0,
//	eBackDeath = 1,
//	eLeftBackDeath = 2
//};

class FallEffectManager : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
	@param	_SceneTag シーンのタグ
	@param _playerPtr プレイヤーのポインタ
	*/
	FallEffectManager(const Tag& _ObjectTag, const SceneBase::SceneType _SceneTag, Player* _playerPtr);

	/*
	@fn	デストラクタ
	*/
	~FallEffectManager() {};

	/*
	@fn		エフェクトマネージャーのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:


	/*
	@fn    速度を決める
	@param _Quantity 個数
	*/
	void DecideVelocity(const int _Quantity);

	//ゲームオブジェクトクラスのポインタ
	GameObject* mOwner;
	//パーティクルの状態
	ParticleState	 mState;
	//シーンのタグ
	SceneBase::SceneType mSceneTag;
	//アタッチしたゲームオブジェクトのタグ
	Tag				 mTag;
	//デスエフェクト
	FallEffect* mFallEffect;
	//プレイヤーのポインタ
	Player* mPlayer;
	// ランダムの速度
	Vector3 mRandVel;

	//任意のタイミングで落ちた時のエフェクトを生成するためのカウント
	int				 mCreateFallEffectCount;

	//角度
	float			 mAngle;

	//落ちた時のエフェクトを一度だけ生成するためのフラグ
	bool			 OneCreateFallFlag;
};

