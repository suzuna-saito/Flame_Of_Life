/*
@file ParticleEffectBase.h
@brief 一定時間で消える、主にエフェクトの基底クラスとして使用されるクラス
*/

/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_pos エフェクトの生成場所
@param	_vel エフェクトの速度
@param	_lifeCount エフェクトの生存時間
@param	_particleFileName 画像へのアドレス
@param	_objectTag アタッチしたゲームオブジェクトのタグ
@param	_sceneTag シーンのタグ
@param	_scale 画像の拡大サイズ
*/
ParticleEffectBase::ParticleEffectBase(const Vector3& _pos, const Vector3& _vel, const int& _lifeCount, const std::string& _particleFileName, SceneBase::Scene _sceneTag, const Tag& _objectTag, bool _billFlag, const float& _scale)
	: GameObject(_sceneTag, _objectTag)
	, mLifeCount(_lifeCount)
	, mAngle(Vector3::Zero)
	, mAlpha(0.0f)
	, mScale(0.0f)
	, mSpeed(0.0f)
	/*, mParticleState(ParticleState::PARTICLE_ACTIVE)*/
{
	mVelocity = _vel;
	mParticle = new ParticleComponent(this, _billFlag);
	mParticle->SetTextureID(RENDERER->GetTexture(_particleFileName)->GetTextureID());
	mParticle->SetColor(Vector3(1.0f, 1.0f, 1.0f));
	mParticle->SetScale(_scale);
	SetPosition(_pos);
}

/*
@fn		派生クラスの更新関数を呼び座標に移動量を足し続ける
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void ParticleEffectBase::UpdateGameObject(float _deltaTime)
{
	LifeCountDown();
	SetPosition(mPosition + mVelocity);
}

/*
@fn 生存時間をカウントダウンする関数。派生クラスで更新関数を決定した場合そこに追加すること。
*/
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

/*
@param _flag 反転を行うか
*/
void ParticleEffectBase::SetReverve(float _flag)
{
	mParticle->SetReverce(_flag);
}