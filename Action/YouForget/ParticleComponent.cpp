/*
@file	ParticleComponent.h
@brief	画像を管理しそれを3D空間上に描画するクラス。
*/

/*
@brief	インクルード
*/
#include "pch.h"

// ビルボード行列
Matrix4 ParticleComponent::mStaticBillboardMat;
// カメラのワールド座標
Vector3 ParticleComponent::mStaticCameraWorldPos;

/*
@fn		コンストラクタ
@param	_owner アタッチするゲームオブジェクトのポインタ
@param	_offset 親オブジェクトクラスと画像を描画する位置の差
@param	_scale 画像の描画サイズ
@param	_updateOrder コンポーネントの更新順番（数値が小さいほど早く更新される）
*/
ParticleComponent::ParticleComponent(GameObject* _owner, bool _billFlag ,const Vector3& _offset, float _scale, int _updateOrder)
	: Component(_owner, _updateOrder)
	, mBlendType(ParticleBlendType::eAlphaBlend)
	, mOffset(_offset)
	, mColor(Vector3(1, 1, 1))
	, mAlpha(1.0f)
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

/*
@fn	デストラクタ
*/
ParticleComponent::~ParticleComponent()
{
	//レンダラーからポインタを削除する
	RENDERER->RemoveParticle(this);
}

/*
@fn		描画処理
@param	_shader 使用するシェーダークラスのポインタ
*/
void ParticleComponent::Draw(Shader* _shader)
{
	//親オブジェクトが未更新状態でないか
	if (mOwner->GetState() == State::Dead)
	{
		return;
	}
	Matrix4 mat, matScale;
	Vector3 reverceVec = Vector3(1, 1, 1);

	//サイズを反転させる
	if (mReverce)
	{
		reverceVec.x *= -1;
	}

	matScale = Matrix4::CreateScale(reverceVec * mOwner->GetScale().x);
	mat = Matrix4::CreateTranslation(mOffset + mOwner->GetPosition());

	// カメラの方向に向かせるかどうかで分岐
	// 向かせる
	if (mBillboardFlag)
	{
		_shader->SetMatrixUniform("uWorldTransform", matScale * mStaticBillboardMat * mat);
	}
	// 向かせない
	else
	{
		// 全てのパーティクルのビルボード行列をセット
		// X軸回転
		if (mAngle.x > 0.0f)
		{
			Matrix4 matRotationX;
			matRotationX = Matrix4::CreateRotationX(mAngle.x * 3.14159f);
			_shader->SetMatrixUniform("uWorldTransform", matScale * matRotationX * mat);
		}
		// Y軸回転
		if (mAngle.y > 0.0f)
		{
			Matrix4 matRotationY;
			matRotationY = Matrix4::CreateRotationY(mAngle.y * 3.14159f);
			_shader->SetMatrixUniform("uWorldTransform", matScale * matRotationY * mat);
		}
		// Z軸回転
		if (mAngle.z > 0.0f)
		{
			Matrix4 matRotationZ;
			matRotationZ = Matrix4::CreateRotationZ(mAngle.z * 3.14159f);
			_shader->SetMatrixUniform("uWorldTransform", matScale * matRotationZ * mat);
		}
	}
	
	_shader->SetFloatUniform("uAlpha", mOwner->GetAlpha());
	_shader->SetVectorUniform("uColor", mColor);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	_shader->SetIntUniform("uParticleTexture", 0);

	RENDERER->SetParticleVertex();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

// カメラ距離でのソート用
bool ParticleComponent::operator<(const ParticleComponent& _rhs) const
{
	float lenThis, lenRhs;
	lenThis = (mStaticCameraWorldPos - mOffset).LengthSq();
	lenRhs = (mStaticCameraWorldPos - _rhs.mOffset).LengthSq();
	return lenThis < lenRhs;
}

// カメラ距離でのソート用
bool ParticleComponent::operator>(const ParticleComponent& _rhs) const
{
	float lenThis, lenRhs;
	lenThis = (mStaticCameraWorldPos - mOffset).LengthSq();
	lenRhs = (mStaticCameraWorldPos - _rhs.mOffset).LengthSq();
	return lenThis > lenRhs;
}

/*
@return ビルボード行列(Matrix4)
*/
Matrix4 GetBillboardMatrix()
{
	Matrix4 ret;
	ret = RENDERER->GetViewMatrix();
	ret.mat[3][0] = ret.mat[3][1] = ret.mat[3][2] = 0.0f;
	ret.Transpose();
	ret.mat[2][2] *= -1;

	Matrix4 rot;
	rot = Matrix4::CreateRotationX(-0.5f * 3.14159f);
	ret = rot * ret;

	return Matrix4(ret);
}