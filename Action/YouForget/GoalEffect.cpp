#include "pch.h"

GoalEffect::GoalEffect(const Vector3 _Pos, const Vector3 _Vel, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, GoalObj* _PlayerPtr)
	: ParticleEffectBase(_Pos, _Vel, 100, "Assets/Effect/Goal.png", _SceneTag, _ObjectTag, false)
{
	mAlpha = 1.0f;
	mScale = 1000.0f;
	mParticle->SetAlpha(mAlpha);
	mParticle->SetScale(mScale);
	mParticle->SetAngle(1.0f);
	mParticle->SetBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ALPHA);
	mVelocity = _Vel;
	mSpeed = 0.005f;

	mGoal = _PlayerPtr;
}

void GoalEffect::UpdateGameObject(float _deltaTime)
{
	if (mAlpha >= 1.0f || mAlpha <= 0.6f)
	{
		mSpeed *= -1.0f;
	}

	if (mRot >= 2.0f)
	{
		mRot = 0.0f;
	}

	mRot += 0.002f;
	mAlpha += mSpeed;

	mParticle->SetAlpha(mAlpha);
	mParticle->SetRot(mRot);
}
