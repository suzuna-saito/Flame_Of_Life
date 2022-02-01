/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
@param	_SceneTag シーンのタグ
@param _playerPtr プレイヤーのポインタ
*/
FallEffectManager::FallEffectManager(const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr)
	:GameObject(_SceneTag, _ObjectTag)
	, mRandVel(Vector3::Zero)
{
	mState = ParticleState::PARTICLE_DISABLE;
	mSceneTag = _SceneTag;
	mTag = _ObjectTag;

	mAngle = 0.0f;

	OneCreateFallFlag = true;

	mPlayer = _playerPtr;
}

/*
@fn		エフェクトマネージャーのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void FallEffectManager::UpdateGameObject(float _deltaTime)
{
	if (!Player::mOperable && mPlayer->GetStartFlag() && OneCreateFallFlag)
	{
		mState = ParticleState::PARTICLE_ACTIVE;
	}
	else
	{
		mState = ParticleState::PARTICLE_DISABLE;
	}

	switch (mState)
	{
	case ParticleState::PARTICLE_DISABLE:

		mCreateFallEffectCount = 0;

		break;
	case ParticleState::PARTICLE_ACTIVE:

		
		mPosition = mPlayer->GetPosition();

		mFallEffect = new FallEffect(mPosition, Vector3::Zero, mTag, mSceneTag);
		
		OneCreateFallFlag = false;

		break;
	}

	if (Player::mOperable)
	{
		OneCreateFallFlag = true;
	}
}

/*
@fn    速度を決める
@param _Quantity 個数
*/
void FallEffectManager::DecideVelocity(const int _Quantity)
{
	////方向の個数
	//const int DirectionNum = 3;
	//向き
	const float Direction = 1.0f;

	mRandVel = Vector3(rand() % 100 + 1.0f, rand() % 100 + 1.0f, rand() % 100 + 1.0f);
	mRandVel.Normalize();

	/*switch (_Quantity % DirectionNum)
	{
	case DirectionDeathEffect::eLeftDeath:
		mRandVel.x *= -Direction;
		break;
	case DirectionDeathEffect::eBackDeath:
		mRandVel.z *= -Direction;
		break;
	case DirectionDeathEffect::eLeftBackDeath:
		mRandVel.x *= -Direction;
		mRandVel.z *= -Direction;
		break;
	}*/
}
