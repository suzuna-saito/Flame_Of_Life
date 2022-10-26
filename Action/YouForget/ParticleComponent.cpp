#include "pch.h"

ParticleComponent::ParticleComponent(GameObject* _owner, bool _billFlag, EffectType _effectType, int _updateOrder)
	: Component(_owner, _updateOrder)
	, mTexture(nullptr)
	, mEffectType(_effectType)
	, mBlendType(ParticleBlendType::eAlphaBlend)
	, mAngle(Vector3::Zero)
	, mDrawOrder(_updateOrder)
	, mTextureID(0)
	, mTextureWidth(0)
	, mTextureHeight(0)
	, mVisible(true)
	, mBillboardFlag(_billFlag)
{
	// �����_���[�Ƀ|�C���^�[�𑗂�
	RENDERER->AddParticle(this);
}

ParticleComponent::~ParticleComponent()
{
	// �����_���[����|�C���^���폜����
	RENDERER->RemoveParticle(this);
}

void ParticleComponent::Draw(Shader* _shader)
{
	// �s����쐬
	Matrix4 mat, matScale;
	mat = Matrix4::CreateTranslation(mOwner->GetPosition());// �|�W�V����
	matScale = Matrix4::CreateScale(mOwner->GetScale());	// �X�P�[��

	//�G�t�F�N�g�̃^�C�v��2D��������
	if (mEffectType == EffectType::e2D)
	{
		// �X�P�[���̍X�V
		matScale = Matrix4::CreateScale(
			static_cast<float>(mTextureWidth) * mOwner->GetScale().x,
			static_cast<float>(mTextureHeight) * mOwner->GetScale().y,
			1.0f);

		// �X�N���[���ʒu�̕��s�ړ�
		mat = Matrix4::CreateTranslation(
			Vector3(mOwner->GetPosition().x,
				mOwner->GetPosition().y,
				0.0f));

		// �s����v�Z
		Matrix4 world = matScale * mat;
		// uWorldTransform��ݒ�
		_shader->SetMatrixUniform("uWorldTransform", world);

	}
	// 3D��������J�����̕����Ɍ������邩�ǂ����ŕ���
	// ��������
	else if (mBillboardFlag)
	{
		// uWorldTransform�ɃJ�����̌����̍s���ݒ�
		mStaticBillboardMat = GetBillboardMatrix();
		_shader->SetMatrixUniform("uWorldTransform", matScale * mStaticBillboardMat * mat);
	}
	// �������Ȃ�
	else
	{
		// uWorldTransform�ɔC�ӂ̍s���ݒ�
		Matrix4 resultMat;
		Matrix4 matRotationX, matRotationY, matRotationZ;

		matRotationX = Matrix4::CreateRotationX(mAngle.x * 3.14159f);	// X����]
		matRotationY = Matrix4::CreateRotationY(mAngle.y * 3.14159f);	// Y����]
		matRotationZ = Matrix4::CreateRotationZ(mAngle.z * 3.14159f);	// Z����]
		resultMat = matRotationX * matRotationY * matRotationZ;
		_shader->SetMatrixUniform("uWorldTransform", matScale * resultMat * mat);
	}

	// �A�^�b�`�����I�u�W�F�N�g�̒l���Z�b�g
	_shader->SetFloatUniform("uAlpha", mOwner->GetAlpha());		// ���l
	_shader->SetVectorUniform("uColor", mOwner->GetColor());	// ��Z�F

	// ���ꂩ��X���b�g���hGL_TEXTURE0���̐ݒ������
	glActiveTexture(GL_TEXTURE0);
	// �e�N�X�`���̊��蓖��
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	// �`��
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

Matrix4 ParticleComponent::GetBillboardMatrix()
{
	// �J�����̌����s����擾
	Matrix4 ret;
	ret = RENDERER->GetViewMatrix();
	ret.mat[3][0] = ret.mat[3][1] = ret.mat[3][2] = 0.0f;
	ret.Transpose();
	ret.mat[2][2] *= -1;

	return Matrix4(ret);
}

void ParticleComponent::SetTexture(Texture* _texture)
{
	// �e�N�X�`�����Z�b�g
	mTexture = _texture;
	// �c�A���̒������擾
	mTextureWidth = mTexture->GetWidth();
	mTextureHeight = mTexture->GetHeight();
}
