#include "pch.h"

CircledShadow::CircledShadow(class GameObject* _owner, const Vector3 _color)
	: ParticleEffectBase(_owner)
	, MBaseZPos(90.0f)
	, MMaxScale(350.0f)
	, MInitOwnerAlpha(mOwner->GetAlpha())
	, MMaxAlpha(0.8f)
	, MAddAlpha(0.02f)
	, MSubAlpha(-0.03f)
{
	// テクスチャをセット
	mParticle->SetTextureID(RENDERER->GetTexture("Assets/Effect/Particle.png")->GetTextureID());
	// 乗算する色を設定
	mParticle->SetColor(_color);
	// 回転値を設定
	mParticle->SetAngle(Vector3(0.5f, 0.0f, 0.0f));
	// ブレンドの種類をαブレンドに設定
	mParticle->SetBlendMode(ParticleComponent::ParticleBlendType::eAlphaBlend);
	
	// GameObjectクラスの変数初期化
	mPosition = _owner->GetPosition();		// ポジション
	mPosition.z = MBaseZPos;
	mScale = Vector3(MMaxScale,0.0f,0.0f);	// スケール
	mAlpha = MMaxAlpha;						// α値
}

void CircledShadow::UpdateGameObject(float _deltaTime)
{
	// ポジションを更新
	mPosition = mOwner->GetPosition();

	// アタッチしたオブジェクトのα値が更新されていたら
	if (MInitOwnerAlpha != mOwner->GetAlpha())
	{
		// α値をアタッチしたオブジェクトのα値に合わせて更新
		mAlpha = mOwner->GetAlpha() - (MInitOwnerAlpha - MMaxAlpha);
	}

	// アタッチしたオブジェクトのポジションが90.0f以上の時
	if (mOwner->GetPosition().z >= MBaseZPos)
	{
		// α値がMMaxAlpha未満だったら
		if (mAlpha < MMaxAlpha)
		{
			mAlpha += MAddAlpha;	// α値を更新
		}

		// ポジション、スケールを更新
		mPosition.z = MBaseZPos;							//ポジションZをMBaseZPosに設定
		mScale.x = MMaxScale - mOwner->GetPosition().z / 4;	// MMaxScale - アタッチしたオブジェクトのポジション/4
	}
	// 上記の条件が一致しなかったとき
	else
	{
		// α値が0.0fより上だったら
		if (mAlpha > 0.0f)
		{
			mAlpha += MSubAlpha;	// α値を更新
		}
	}
}