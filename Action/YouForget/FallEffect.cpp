#include "pch.h"

/*
@fn		コンストラクタ
@param	_Pos デスエフェクトの生成場所
@param	_Vel クリアエフェクトの速度
@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
@param	_SceneTag シーンのタグ
*/

FallEffect::FallEffect(const Vector3 _Pos, const Vector3 _Vel, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	:ParticleEffectBase(_Pos, _Vel, 40, "Assets/Effect/Ripple.png", _SceneTag, _ObjectTag,false)
	, MAlphaReductionVal(0.03f)
	, MScaleAddVal(10.0f)
{
	mAngle.x = 0.5f;
	mAlpha = 1.0f;
	mScale = 200.0f;
	mParticle->SetAngle(mAngle);
	mParticle->SetAlpha(mAlpha);
	mParticle->SetScale(mScale);
	//mParticle->SetColor(Color::LightBlue);
	mParticle->SetColor(Color::Red);
	mParticle->SetBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ALPHA);
	mVelocity = _Vel;
}

/*
@fn		デスエフェクトのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void FallEffect::UpdateGameObject(float _deltaTime)
{
	//生存時間をカウント
	ParticleEffectBase::LifeCountDown();

	//ライフカウントが0より大きかったら速度、透明度、スケールの値を更新
	if (mLifeCount > 0)
	{
		mAlpha -= MAlphaReductionVal;
		mScale += MScaleAddVal;

		mParticle->SetAlpha(mAlpha);
		mParticle->SetScale(mScale);
	}

	//ライフカウントが0以下だったら見えなくする
	if (mAlpha <= 0.0f)
	{
		mParticle->SetVisible(false);
	}
}
