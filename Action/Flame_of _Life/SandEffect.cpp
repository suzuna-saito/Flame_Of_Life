/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_pos 砂ぼこりの座標
@param	_vel 砂ぼこりの速度
@param	_objectTag アタッチしたゲームオブジェクトのタグ
@param	_sceneTag シーンのタグ
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
@fn		砂ぼこりのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
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
