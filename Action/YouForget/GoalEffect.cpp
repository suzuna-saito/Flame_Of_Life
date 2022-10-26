#include "pch.h"

GoalEffect::GoalEffect(class GameObject* _owner)
	: ParticleEffectBase(_owner)
	, MAddAngleY(0.002f)
	, MMInAlpha(0.6f)
	, mAddScale(1.5f)
	, mAddAlpha(0.005f)
{
	// テクスチャをセット
	mParticle->SetTexture(RENDERER->GetTexture("Assets/Effect/Goal.png"));
	// ブレンドの種類をαブレンドに設定
	mParticle->SetBlendMode(ParticleComponent::ParticleBlendType::eAlphaBlend);
	
	// スケール値（単体）を設定
	mFloatScale = 1000.0f;

	// GameObjectクラスの変数初期化
	mPosition = mOwner->GetPosition();					// ポジション
	mScale = Vector3(mFloatScale, 1.0f, mFloatScale);	// スケール
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
	mAngle.y += MAddAngleY;		// 回転値
	mAlpha += mAddAlpha;		// α値
	mFloatScale += mAddScale;	// スケール
	mScale = Vector3(mFloatScale, 1.0f, mFloatScale);

	// 回転値を設定
	mParticle->SetAngle(mAngle);
}