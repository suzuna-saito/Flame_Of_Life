/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_Pos アイテムエフェクトの生成場所
@param	_Vel アイテムエフェクトの速度
@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
@param	_SceneTag シーンのタグ
*/
ItemEffect::ItemEffect(const Vector3 _Pos, const Vector3 _Vel, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Item* _ItemPtr)
	:ParticleEffectBase(_Pos, _Vel, 100, "Assets/Effect/Particle.png", _SceneTag, _ObjectTag)
	, mItemVisible(true)
{
	mAlpha = 0.7f;
	mScale = 500.0f;
	mParticle->SetAlpha(mAlpha);
	mParticle->SetScale(mScale);
	mParticle->SetColor(Color::White);
	mParticle->SetBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ALPHA);
	mVelocity = _Vel;
	mSpeed = 1.15f;

	mItem = _ItemPtr;
}

/*
@fn		デスエフェクトのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void ItemEffect::UpdateGameObject(float _deltaTime)
{

	//アルファ値の削減値
	const float AlphaReductionVal = 0.02f;
	////スケールの追加値
	//const float ScaleAddVal = 1.0f;

	//if(mAlpha>0.)

	//アイテムを取ったら見えなくする
	if (mItem->mGetItemFlag())
	{
		if (mAlpha >= 0.0f)
		{
			mAlpha -= AlphaReductionVal;
		}
		else
		{
			mParticle->SetVisible(false);
			mItemVisible = false;
		}
	}
	
	//ライフカウントが0より大きかったら速度、透明度、スケールの値を更新
	mParticle->SetAlpha(mAlpha);
	mParticle->SetScale(mScale);


}
