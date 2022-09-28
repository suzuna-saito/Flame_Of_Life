/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_owner �Q�[���I�u�W�F�N�g�N���X�̃|�C���^
@param	_objectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
@param	_sceneTag �V�[���̃^�O
*/
EffectManager::EffectManager(GameObject* _owner, const Tag& _objectTag, SceneBase::Scene _sceneTag)
	:GameObject(_sceneTag, _objectTag)
	, mSandEffect(nullptr)
	, mCreateSandEffectCount(0)
	, mCreateDeathEffectCount(0)
{
	mOwner = _owner;
	mState = ParticleState::PARTICLE_DISABLE;
	mPos = Vector3::Zero;
	mSceneTag = _sceneTag;
	mTag = _objectTag;
	mAngle = 0.0f;
}

/*
@fn		�G�t�F�N�g�}�l�[�W���[�̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void EffectManager::UpdateGameObject(float _deltaTime)
{
	if (mPos != mOwner->GetPosition())
	{
		mState = ParticleState::PARTICLE_ACTIVE;
	}
	else
	{
		mState = ParticleState::PARTICLE_DISABLE;
	}

	Vector3 vel = Vector3(0.0f, 0.0f, 0.0f);

	switch (mState)
	{
	case ParticleState::PARTICLE_DISABLE:
		break;
	case ParticleState::PARTICLE_ACTIVE:

		mCreateSandEffectCount++;
		mPosition = mOwner->GetPosition();
		mPosition.y -= 10.0f;
		mPosition.z -= 20.0f;
		if (mCreateSandEffectCount % 6 == 0)
		{

			vel = Vector3(0.0f, 0.0f, -1.0);
			//mSandEffect = new SandEffect(mPosition, vel, mSceneTag, mTag);

		}
		break;
	}

	mPos = mOwner->GetPosition();
}
