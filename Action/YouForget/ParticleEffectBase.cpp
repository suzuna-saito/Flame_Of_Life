#include "pch.h"

ParticleEffectBase::ParticleEffectBase(class GameObject* _owner, bool _billFlag)
	: GameObject(SceneBase::mIsSceneType)
	, mAngle(Vector3::Zero)
	, mOwner(_owner)
	, mFloatScale(0.0f)
{
	// ParticleComponent�𐶐����邱�ƂŎ����ŕ`�悳���悤�ɂȂ�
	mParticle = new ParticleComponent(this, _billFlag);

	// �A�^�b�`�����I�u�W�F�N�g�̃|�C���^
	mOwner = _owner;
}