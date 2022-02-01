/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
@param	_SceneTag シーンのタグ
@param _ItemPtr アイテムのポインタ
*/
ItemEffectManager::ItemEffectManager(const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Item* _ItemPtr)
	:GameObject(_SceneTag, _ObjectTag)
	, mRandVel(Vector3::Zero)
	, farstFlag(true)
{
	mState = ParticleState::PARTICLE_ACTIVE;
	mSceneTag = _SceneTag;
	mTag = _ObjectTag;

	mAngle = 0.0f;

	OneCreateItemFlag = true;

	mItem = _ItemPtr;

	mPosition = mItem->GetPosition();
	mPosition.z = mItem->GetPosition().z - 100.0f;

	mItemEffect = new ItemEffect(mPosition, Vector3::Zero, mTag, mSceneTag,mItem);
}

/*
@fn		エフェクトマネージャーのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void ItemEffectManager::UpdateGameObject(float _deltaTime)
{
	if (!mItemEffect->GetItemVisible() && OneCreateItemFlag)
	{
		mCreateItemEffectCount = 0;
		mState = ParticleState::PARTICLE_DISABLE;
		OneCreateItemFlag = false;
	}

	//if (!mItem->mGetItemFlag() && OneCreateItemFlag)
	//{
	//	mState = ParticleState::PARTICLE_ACTIVE;
	//}
	//else
	//{
	//	mState = ParticleState::PARTICLE_DISABLE;
	//}

	//switch (mState)
	//{
	//case ParticleState::PARTICLE_DISABLE:

	//	mCreateItemEffectCount = 0;

	//	break;
	//case ParticleState::PARTICLE_ACTIVE:

	//	mPosition = mItem->GetPosition();

	//	if (farstFlag)
	//	{
	//		mItemEffect = new ItemEffect(mPosition, Vector3::Zero, mTag, mSceneTag);
	//		farstFlag = false;
	//	}

	//	//OneCreateItemFlag = false;

	//	break;
	//}

	//// アイテムを取得したらエフェクトを消す
	//if (mItem->mGetItemFlag())
	//{
	//	OneCreateItemFlag = false;
	//}

}

/*
@fn    速度を決める
@param _Quantity 個数
*/
void ItemEffectManager::DecideVelocity(const int _Quantity)
{
	////方向の個数
	//const int DirectionNum = 3;
	////向き
	//const float Direction = 1.0f;

	//mRandVel = Vector3(rand() % 100 + 0.5f, rand() % 100 + 0.5f, rand() % 100 + 0.5f);
	//mRandVel.Normalize();

	//switch (_Quantity % DirectionNum)
	//{
	//case (int)DirectionItemEffect::eLeftDeath:
	//	mRandVel.x *= -Direction;
	//	break;
	//case (int)DirectionItemEffect::eBackDeath:
	//	mRandVel.z *= -Direction;
	//	break;
	//case (int)DirectionItemEffect::eLeftBackDeath:
	//	mRandVel.x *= -Direction;
	//	mRandVel.z *= -Direction;
	//	break;
	//}
}
