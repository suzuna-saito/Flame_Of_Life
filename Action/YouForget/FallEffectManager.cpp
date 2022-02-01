/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
@param	_SceneTag �V�[���̃^�O
@param _playerPtr �v���C���[�̃|�C���^
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
@fn		�G�t�F�N�g�}�l�[�W���[�̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
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
@fn    ���x�����߂�
@param _Quantity ��
*/
void FallEffectManager::DecideVelocity(const int _Quantity)
{
	////�����̌�
	//const int DirectionNum = 3;
	//����
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
