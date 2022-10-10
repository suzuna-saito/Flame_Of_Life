#include "pch.h"

GoalEffect::GoalEffect(const Vector3 _Pos, const Vector3 _Vel, const Tag& _ObjectTag, const SceneBase::SceneType _SceneTag, GoalObj* _PlayerPtr)
	: ParticleEffectBase()
{

	// テクスチャをセット
	mParticle->SetTextureID(RENDERER->GetTexture("Assets/Effect/Goal.png")->GetTextureID());

	mAlpha = 1.0f;
	mScale = Vector3(1000.0f, 1.0f, 1.0f);
	mParticle->SetAlpha(mAlpha);
	mParticle->SetBlendMode(ParticleComponent::ParticleBlendType::eAlphaBlend);
	mVelocity = _Vel;
	mMoveSpeed = 0.005f;

	mGoal = _PlayerPtr;
}

void GoalEffect::UpdateGameObject(float _deltaTime)
{
	if (mAlpha >= 1.0f || mAlpha <= 0.6f)
	{
		mMoveSpeed *= -1.0f;
	}

	if (mAngle.y >= 2.0f)
	{
		mAngle.y = 0.0f;
	}

	mAngle.y += 0.002f;
	mAlpha += mMoveSpeed;
	mScale.x += mMoveSpeed * 300.0f;

	mParticle->SetAlpha(mAlpha);
	mParticle->SetAngle(mAngle);
}
