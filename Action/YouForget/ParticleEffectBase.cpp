#include "pch.h"

ParticleEffectBase::ParticleEffectBase()
	: GameObject(SceneBase::mIsSceneType)
	, mAngle(Vector3::Zero)
{
	// ParticleComponentを生成することで自動で描画されるようになる
	mParticle = new ParticleComponent(this);
}

void ParticleEffectBase::UpdateGameObject(float _deltaTime)
{
	LifeCountDown();
	SetPosition(mPosition + mVelocity);
}

void ParticleEffectBase::LifeCountDown()
{
	//生存時間がゼロになるとこのオブジェクトを更新終了する
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