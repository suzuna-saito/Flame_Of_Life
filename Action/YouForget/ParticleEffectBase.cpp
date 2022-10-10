#include "pch.h"

ParticleEffectBase::ParticleEffectBase(class GameObject* _owner, bool _billFlag)
	: GameObject(SceneBase::mIsSceneType)
	, mAngle(Vector3::Zero)
	, mOwner(_owner)
	, mFloatScale(0.0f)
{
	// ParticleComponentを生成することで自動で描画されるようになる
	mParticle = new ParticleComponent(this, _billFlag);

	// アタッチしたオブジェクトのポインタ
	mOwner = _owner;
}