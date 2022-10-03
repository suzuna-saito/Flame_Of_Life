#include "pch.h"

CircledShadow::CircledShadow(const Vector3 _Pos, const Vector3 _Vel, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _PlayerPtr)
	: ParticleEffectBase(_Pos, _Vel, 100, "Assets/Effect/Particle.png", _SceneTag, _ObjectTag, false)
{
	mAngle.x = 0.5f;
	mAlpha = 1.0f;
	mScale = 300.0f;
	mParticle->SetAngle(mAngle);
	mParticle->SetAlpha(mAlpha);
	mParticle->SetScale(mScale);
	mParticle->SetColor(Color::LightPink);
	mParticle->SetBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ALPHA);
	mVelocity = _Vel;
	mSpeed = 1.15f;

	mPlayer = _PlayerPtr;
}

void CircledShadow::UpdateGameObject(float _deltaTime)
{
	mPosition = mPlayer->GetPosition();

	if (mPosition.z >= 90.0f)
	{
		if (mAlpha <= 1.0f)
		{
			mAlpha += 0.05f;
		}

		mPosition.z = 90.0f;

		float maxScale = 300.0f;
		mScale = maxScale - mPlayer->GetPosition().z / 4;
	}
	else
	{
		mAlpha -= 0.07f;
	}

	mParticle->SetAlpha(mAlpha);
	mParticle->SetScale(mScale);
}
