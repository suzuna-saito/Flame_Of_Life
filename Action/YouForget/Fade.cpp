#include "pch.h"

// 静的メンバ変数の初期化
bool Fade::mFadeFlag = false;

Fade::Fade()
	: ParticleEffectBase(nullptr)
	, mFadeSpeed(0.01f)
{
	// テクスチャをセット
	mParticle->SetTextureID(RENDERER->GetTexture("Assets/UI/Fade/Fade.png")->GetTextureID());
	// ブレンドの種類をαブレンドに設定
	mParticle->SetBlendMode(ParticleComponent::ParticleBlendType::eAlphaBlend);

	// GameObjectクラスの変数初期化
	mScale = Vector3(1920.0f, 1080.0f, 0.0f);	// スケール
}

void Fade::UpdateGameObject(float _deltaTime)
{
	// mFadeFlagフラグがtrueだったら
	if (mFadeFlag)
	{
		// α値の更新
		mAlpha -= mFadeSpeed;
		// α値が0.0f以下、もしくは1.0f以上になったら
		if (mAlpha <= 0.0f || mAlpha >= 1.0f)
		{
			// フェードの更新をやめる
			mFadeFlag = false;
		}
	}
}

void Fade::SetFade(Vector3 _color, FadeType _fadeType)
{
	// 色の設定
	mColor = _color;

	// フェードインの時
	if (_fadeType == FadeType::eIn)
	{
		// α値 : 1.0f
		mAlpha = 1.0f;
		// mFadeSpeedが負の数だったら
		if (mFadeSpeed < 0.0f)
		{
			mFadeSpeed *= -1;	// 符号を変える
		}
	}
	// フェードアウトの時
	else
	{
		// α値 : 0.0f
		mAlpha = 0.0f;
		// mFadeSpeedが正の数だったら
		if (mFadeSpeed > 0.0f)
		{
			mFadeSpeed *= -1;	// 符号を変える
		}
	}

	// フェードの更新処理を始める
	mFadeFlag = true;
}
