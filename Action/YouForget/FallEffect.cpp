#include "pch.h"

FallEffect::FallEffect(class GameObject* _owner)
	:ParticleEffectBase(_owner)
	, MBaseScale(200.0f)
	, MAddScale(10.0f)
	, MSubAlpha(-0.03f)
	, mTmpVisible(false)
{
	// テクスチャをセット
	mParticle->SetTextureID(RENDERER->GetTexture("Assets/Effect/Ripple.png")->GetTextureID());
	// 乗算する色を設定
	mParticle->SetColor(Color::Red);
	// 回転値を設定
	mParticle->SetAngle(Vector3(0.5f, 0.0, 0.0f));
	// ブレンドの種類をαブレンドに設定
	mParticle->SetBlendMode(ParticleComponent::ParticleBlendType::eAlphaBlend);
	// 描画をするかどうかを設定
	mParticle->SetVisible(false);
	
	// GameObjectクラスの変数初期化
	mScale = Vector3(MBaseScale, 1.0f, 1.0f);	// スケール
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
		mAlpha = 1.0f;			// α値
		mScale.x = MBaseScale;	// スケール

		// 描画フラグをfalseにする
		mParticle->SetVisible(false);
	}

	// 描画フラグがtrueだったら
	if (mParticle->GetVisible())
	{
		// α値、スケールを更新
		mAlpha += MSubAlpha;	// α値
		mScale.x += MAddScale;	// スケール
	}

	// 描画していたかどうかを保存
	mTmpVisible = mParticle->GetVisible();
}