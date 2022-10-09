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
ItemEffect::ItemEffect(const Vector3 _Pos, const Vector3 _Vel, const Tag& _ObjectTag, const SceneBase::SceneType _SceneTag, Item* _ItemPtr)
	:ParticleEffectBase()
	, mItemVisible(true)
{
	// テクスチャをセット
	mParticle->SetTextureID(RENDERER->GetTexture("Assets/Effect/Particle.png")->GetTextureID());

	mAngle.x = 0.5f;
	mAlpha = 0.7f;
	mScale = Vector3(500.0f, 1.0f, 1.0f);
	mParticle->SetAngle(mAngle);
	mParticle->SetAlpha(mAlpha);
	mParticle->SetColor(Color::White);
	mParticle->SetBlendMode(ParticleComponent::ParticleBlendType::eAlphaBlend);
	mVelocity = _Vel;
	mMoveSpeed = 1.15f;

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

	//アイテムが存在してなかったら見えなくする
	if (!mItem->mGetItemExistsFlag())
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
	
	//ライフカウントが0より大きかったら透明度、スケールの値を更新
	mParticle->SetAlpha(mAlpha);
}
