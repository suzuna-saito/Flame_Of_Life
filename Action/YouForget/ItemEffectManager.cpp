/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
@param	_SceneTag �V�[���̃^�O
@param _ItemPtr �A�C�e���̃|�C���^
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
@fn		�G�t�F�N�g�}�l�[�W���[�̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
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

	//// �A�C�e�����擾������G�t�F�N�g������
	//if (mItem->mGetItemFlag())
	//{
	//	OneCreateItemFlag = false;
	//}

}

/*
@fn    ���x�����߂�
@param _Quantity ��
*/
void ItemEffectManager::DecideVelocity(const int _Quantity)
{
	////�����̌�
	//const int DirectionNum = 3;
	////����
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
