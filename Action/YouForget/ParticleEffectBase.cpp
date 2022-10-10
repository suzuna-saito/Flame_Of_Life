#include "pch.h"

ParticleEffectBase::ParticleEffectBase(class GameObject* _owner)
	: GameObject(SceneBase::mIsSceneType)
	, mAngle(Vector3::Zero)
	, mOwner(_owner)
{
	// ParticleComponentを生成することで自動で描画されるようになる
	mParticle = new ParticleComponent(this);

	// アタッチしたオブジェクトのポインタ
	mOwner = _owner;
}

void ParticleEffectBase::UpdateGameObject(float _deltaTime)
{
	//LifeCountDown();
	//SetPosition(mPosition + mVelocity);
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