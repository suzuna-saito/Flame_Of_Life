/*
@file	ParticleComponent.h
@brief	�摜���Ǘ��������3D��ԏ�ɕ`�悷��N���X�B
*/

/*
@brief	�C���N���[�h
*/
#include "pch.h"

// �r���{�[�h�s��
Matrix4 ParticleComponent::mStaticBillboardMat;
// �J�����̃��[���h���W
Vector3 ParticleComponent::mStaticCameraWorldPos;

/*
@fn		�R���X�g���N�^
@param	_owner �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
@param	_offset �e�I�u�W�F�N�g�N���X�Ɖ摜��`�悷��ʒu�̍�
@param	_scale �摜�̕`��T�C�Y
@param	_updateOrder �R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j
*/
ParticleComponent::ParticleComponent(GameObject* _owner, const Vector3& _offset, float _scale, int _updateOrder)
	: Component(_owner, _updateOrder)
	, mBlendType(PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ALPHA)
	, mOffset(_offset)
	, mColor(Vector3(1, 1, 1))
	, mScale(_scale)
	, mAlpha(1.0f)
	, mVisible(true)
	, mReverce(false)
	, mDrawOrder(_updateOrder)
	, mTextureID(0)

{
	//�����_���[�Ƀ|�C���^�[�𑗂�
	RENDERER->AddParticle(this);
}

/*
@fn	�f�X�g���N�^
*/
ParticleComponent::~ParticleComponent()
{
	//�����_���[����|�C���^���폜����
	RENDERER->RemoveParticle(this);
}

/*
@fn		�`�揈��
@param	_shader �g�p����V�F�[�_�[�N���X�̃|�C���^
*/
void ParticleComponent::Draw(Shader* _shader)
{
	//�e�I�u�W�F�N�g�����X�V��ԂłȂ���
	if (mOwner->GetState() == State::Dead)
	{
		return;
	}
	Matrix4 mat, matScale;
	Vector3 reverceVec = Vector3(1, 1, 1);
	//�T�C�Y�𔽓]������
	if (mReverce)
	{
		reverceVec.x *= -1;
	}
	matScale = Matrix4::CreateScale(mScale * reverceVec * mOwner->GetScale());
	mat = Matrix4::CreateTranslation(mOffset + mOwner->GetPosition());

	_shader->SetMatrixUniform("uWorldTransform", matScale * mStaticBillboardMat * mat);
	_shader->SetFloatUniform("uAlpha", mAlpha);
	_shader->SetVectorUniform("uColor", mColor);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	_shader->SetIntUniform("uParticleTexture", 0);

	RENDERER->SetParticleVertex();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

// �J���������ł̃\�[�g�p
bool ParticleComponent::operator<(const ParticleComponent& _rhs) const
{
	float lenThis, lenRhs;
	lenThis = (mStaticCameraWorldPos - mOffset).LengthSq();
	lenRhs = (mStaticCameraWorldPos - _rhs.mOffset).LengthSq();
	return lenThis < lenRhs;
}

// �J���������ł̃\�[�g�p
bool ParticleComponent::operator>(const ParticleComponent& _rhs) const
{
	float lenThis, lenRhs;
	lenThis = (mStaticCameraWorldPos - mOffset).LengthSq();
	lenRhs = (mStaticCameraWorldPos - _rhs.mOffset).LengthSq();
	return lenThis > lenRhs;
}


//Matrix4 GetBillboardMatrix()
//{
//	Matrix4 ret;
//	ret = RENDERER->GetViewMatrix();
//	ret.mat[3][0] = ret.mat[3][1] = ret.mat[3][2] = 0.0f;
//	ret.Transpose();
//	ret.mat[1][1] *= -1;
//	ret.mat[2][2] *= -1;
//
//	return Matrix4(ret);
//}
