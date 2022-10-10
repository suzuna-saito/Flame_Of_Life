#include "pch.h"

CircledShadow::CircledShadow(class GameObject* _owner)
	: ParticleEffectBase()
	, MBaseZPos(90.0f)
	, MMaxScale(300.0f)
	, MAddAlpha(0.03f)
	, MSubAlpha(-0.07f)
{
	// テクスチャをセット
	mParticle->SetTextureID(RENDERER->GetTexture("Assets/Effect/Particle.png")->GetTextureID());
	// 乗算する色を設定
	mParticle->SetColor(Color::LightPink);
	// 回転値を設定
	mParticle->SetAngle(Vector3(0.5f, 0.0f, 0.0f));
	// ブレンドの種類をαブレンドに設定
	mParticle->SetBlendMode(ParticleComponent::ParticleBlendType::eAlphaBlend);
	
	// GameObjectクラスの変数初期化
	mPosition = _owner->GetPosition();		// ポジション
	mPosition.z = MBaseZPos;
	mScale = Vector3(MMaxScale,0.0f,0.0f);	// スケール
	mMoveSpeed = 1.15f;						// 値の変化値

	// アタッチしたオブジェクトのポインタ
	mOwner = _owner;
}

void CircledShadow::UpdateGameObject(float _deltaTime)
{
	// ポジションを更新
	mPosition = mOwner->GetPosition();

	// アタッチしたオブジェクトのポジションが90.0f以上の時
	if (mOwner->GetPosition().z >= MBaseZPos)
	{
		// α値が1.0f未満だったら
		if (mAlpha < 1.0f)
		{
			// α値を変更
			mAlpha += MAddAlpha;
		}

		// ポジションZを90.0fに設定
		mPosition.z = MBaseZPos;
		// スケールを更新
		mScale.x = MMaxScale - mOwner->GetPosition().z / 4;// MMaxScale - アタッチしたオブジェクトのポジション/4
	}
	// アタッチしたオブジェクトのポジションが90.0f未満の時
	else
	{
		// α値が0.0fより上だったら
		if (mAlpha > 0.0f)
		{
			// α値を変更
			mAlpha += MSubAlpha;
		}
	}
}