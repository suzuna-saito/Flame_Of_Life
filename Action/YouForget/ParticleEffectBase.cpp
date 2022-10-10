#include "pch.h"

ParticleEffectBase::ParticleEffectBase(class GameObject* _owner)
	: GameObject(SceneBase::mIsSceneType)
	, mAngle(Vector3::Zero)
	, mOwner(_owner)
{
	// ParticleComponent�𐶐����邱�ƂŎ����ŕ`�悳���悤�ɂȂ�
	mParticle = new ParticleComponent(this);

	// �A�^�b�`�����I�u�W�F�N�g�̃|�C���^
	mOwner = _owner;
}

void ParticleEffectBase::UpdateGameObject(float _deltaTime)
{
	//LifeCountDown();
	//SetPosition(mPosition + mVelocity);
}

void ParticleEffectBase::LifeCountDown()
{
	//�������Ԃ��[���ɂȂ�Ƃ��̃I�u�W�F�N�g���X�V�I������
	if (mLifeCount <= 0)
	{
		mParticle->SetVisible(false);
		SetState(State::Dead);
	}
	else
	{
		mParticle->SetVisible(true);
		mLifeCount--;
	}

}

void ParticleEffectBase::SetReverve(float _flag)
{
	mParticle->SetReverce(_flag);
}