#include "pch.h"

ParticleComponent::ParticleComponent(GameObject* _owner, bool _billFlag, EffectType _effectType, int _updateOrder)
	: Component(_owner, _updateOrder)
	, mBlendType(ParticleBlendType::eAlphaBlend)
	, mEffectType(_effectType)
	, mAngle(Vector3::Zero)
	, mVisible(true)
	, mReverce(false)
	, mDrawOrder(_updateOrder)
	, mTextureID(0)
	, mBillboardFlag(_billFlag)
{
	//レンダラーにポインターを送る
	RENDERER->AddParticle(this);
}

ParticleComponent::~ParticleComponent()
{
	//レンダラーからポインタを削除する
	RENDERER->RemoveParticle(this);
}

void ParticleComponent::Draw(Shader* _shader)
{
	//親オブジェクトが未更新状態だったら
	if (mOwner->GetState() == State::Dead)
	{
		return;
	}

	// 行列を作成
	Matrix4 mat, matScale;
	matScale = Matrix4::CreateScale(mOwner->GetScale());	// スケール
	mat = Matrix4::CreateTranslation(mOwner->GetPosition());// ポジション

	//エフェクトのタイプが2Dだったら
	if (mEffectType == EffectType::e2D)
	{
		// スケールの更新
		matScale = Matrix4::CreateScale(
			static_cast<float>(1.0f) * mOwner->GetScale().x,
			static_cast<float>(1.0f) * mOwner->GetScale().y,
			1.0f);

		// スクリーン位置の平行移動
		mat = Matrix4::CreateTranslation(
			Vector3(mOwner->GetPosition().x,
				mOwner->GetPosition().y,
				0.0f));

		// 行列を計算
		Matrix4 world = matScale * mat;
		// uWorldTransformを設定
		_shader->SetMatrixUniform("uWorldTransform", world);

	}
	// 3Dだったらカメラの方向に向かせるかどうかで分岐
	// 向かせる
	else if (mBillboardFlag)
	{
		// uWorldTransformにカメラの向きの行列を設定
		mStaticBillboardMat = GetBillboardMatrix();
		_shader->SetMatrixUniform("uWorldTransform", matScale * mStaticBillboardMat * mat);
	}
	// 向かせない
	else
	{
		// uWorldTransformに任意の行列を設定
		Matrix4 resultMat;
		Matrix4 matRotationX, matRotationY, matRotationZ;

		matRotationX = Matrix4::CreateRotationX(mAngle.x * 3.14159f);	// X軸回転
		matRotationY = Matrix4::CreateRotationY(mAngle.y * 3.14159f);	// Y軸回転
		matRotationZ = Matrix4::CreateRotationZ(mAngle.z * 3.14159f);	// Z軸回転
		resultMat = matRotationX * matRotationY * matRotationZ;
		_shader->SetMatrixUniform("uWorldTransform", matScale * resultMat * mat);
	}

	// アタッチしたオブジェクトの値をセット
	_shader->SetFloatUniform("uAlpha", mOwner->GetAlpha());		// α値
	_shader->SetVectorUniform("uColor", mOwner->GetColor());	// 乗算色

	// これからスロット名”GL_TEXTURE0″の設定をする
	glActiveTexture(GL_TEXTURE0);
	// テクスチャの割り当て
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	// 描画
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

bool ParticleComponent::operator<(const ParticleComponent& _rhs) const
{
	float lenThis, lenRhs;
	lenThis = (mStaticCameraWorldPos).LengthSq();
	lenRhs = (mStaticCameraWorldPos).LengthSq();
	return lenThis < lenRhs;
}

bool ParticleComponent::operator>(const ParticleComponent& _rhs) const
{
	float lenThis, lenRhs;
	lenThis = (mStaticCameraWorldPos).LengthSq();
	lenRhs = (mStaticCameraWorldPos).LengthSq();
	return lenThis > lenRhs;
}

Matrix4 GetBillboardMatrix()
{
	// カメラの向き行列を取得
	Matrix4 ret;
	ret = RENDERER->GetViewMatrix();
	ret.mat[3][0] = ret.mat[3][1] = ret.mat[3][2] = 0.0f;
	ret.Transpose();
	ret.mat[2][2] *= -1;

	return Matrix4(ret);
}