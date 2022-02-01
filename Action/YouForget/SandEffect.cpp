/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_pos ���ڂ���̍��W
@param	_vel ���ڂ���̑��x
@param	_objectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
@param	_sceneTag �V�[���̃^�O
*/
SandEffect::SandEffect(Vector3 _pos, Vector3 _vel, SceneBase::Scene _sceneTag, const Tag& _objectTag)
	:ParticleEffectBase(_pos, _vel, 90, "Assets/PhotonB.png", _sceneTag, _objectTag)
{
	mAlpha = 0.5f;
	mScale = 32.0f;
	mParticle->SetAlpha(mAlpha);
	mParticle->SetScale(mScale);
	mParticle->SetColor(Vector3(0.95f, 0.95f, 0.95f));
	mParticle->SetBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ALPHA);
	mSpeed = 1.0f;
}

/*
@fn		���ڂ���̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void SandEffect::UpdateGameObject(float _deltaTime)
{
	ParticleEffectBase::LifeCountDown();

	if (mLifeCount > 0)
	{
		mAlpha -= 0.01f;
		mScale += 10.0f;
		mParticle->SetAlpha(mAlpha);
		mParticle->SetScale(mScale);
		mVelocity = mVelocity * mSpeed;
		mPosition = mPosition + mVelocity;
		SetPosition(mPosition);
	}

	if (mLifeCount <= 0)
	{
		mParticle->SetVisible(false);
	}
}
