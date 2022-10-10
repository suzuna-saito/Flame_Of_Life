#include "pch.h"

GoalEffect::GoalEffect(class GameObject* _owner)
	: ParticleEffectBase(_owner)
	, MAddAngleY(0.002f)
	, MMInAlpha(0.6f)
	, mAddScale(1.5f)
	, mAddAlpha(0.005f)
{
	// テクスチャをセット
	mParticle->SetTextureID(RENDERER->GetTexture("Assets/Effect/Goal.png")->GetTextureID());
	// ブレンドの種類をαブレンドに設定
	mParticle->SetBlendMode(ParticleComponent::ParticleBlendType::eAlphaBlend);
	
	// GameObjectクラスの変数初期化
	mPosition = mOwner->GetPosition();		// ポジション
	mScale = Vector3(1000.0f, 1.0f, 1.0f);	// スケール
}

void GoalEffect::UpdateGameObject(float _deltaTime)
{
	// α値が1.0f以上、または0.6f以下の時
	if (mAlpha >= 1.0f || mAlpha <= MMInAlpha)
	{
		// 値の変化値の符号更新
		mAddAlpha *= -1.0f;
		mAddScale *= -1.0f;
	}

	// アングルが一回転した時
	if (mAngle.y >= 2.0f)
	{
		// 初期値に戻す
		mAngle.y = 0.0f;
	}

	// 回転値、α値、スケールの更新
	mAngle.y += MAddAngleY;	// 回転値
	mAlpha += mAddAlpha;	// α値
	mScale.x += mAddScale;	// スケール

	// 回転値を設定
	mParticle->SetAngle(mAngle);
}