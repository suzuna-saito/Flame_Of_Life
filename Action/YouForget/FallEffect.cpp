#include "pch.h"

FallEffect::FallEffect(class GameObject* _owner)
	:ParticleEffectBase(_owner)
	, MBaseScale(200.0f)
	, MAddScale(10.0f)
	, MSubAlpha(-0.03f)
	, mTmpVisible(false)
{
	// テクスチャをセット
	mParticle->SetTexture(RENDERER->GetTexture("Assets/Effect/Ripple.png"));
	// 回転値を設定
	mParticle->SetAngle(Vector3(0.5f, 0.0, 0.0f));
	// ブレンドの種類をαブレンドに設定
	mParticle->SetBlendMode(ParticleComponent::ParticleBlendType::eAlphaBlend);
	// 描画をするかどうかを設定
	mParticle->SetVisible(false);
	
	// スケール値のfloat値を代入
	mFloatScale = MBaseScale;

	// GameObjectクラスの変数初期化
	mScale = Vector3(MBaseScale, 1.0f, MBaseScale);	// スケール
	mColor = Color::Red;							// 乗算する色
}

void FallEffect::UpdateGameObject(float _deltaTime)
{
	// 描画フラグが外部から変更された時
	if (mTmpVisible != mParticle->GetVisible())
	{
		// 描画ポジションを更新
		mPosition = mOwner->GetPosition();
	}

	// α値が0.0f以下だったら
	if (mAlpha <= 0.0f)
	{
		// α値、スケールを初期値に戻す
		mAlpha = 1.0f;				// α値
		mFloatScale = MBaseScale;	// スケール

		// 描画フラグをfalseにする
		mParticle->SetVisible(false);
	}

	// 描画フラグがtrueだったら
	if (mParticle->GetVisible())
	{
		// α値、スケールを更新
		mAlpha += MSubAlpha;		// α値
		mFloatScale += MAddScale;	// スケール
	}

	// スケールを更新
	mScale = Vector3(mFloatScale, 1.0f, mFloatScale);
	// 描画していたかどうかを保存
	mTmpVisible = mParticle->GetVisible();
}