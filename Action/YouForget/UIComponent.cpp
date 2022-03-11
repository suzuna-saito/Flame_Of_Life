/*
@file  SpriteComponent.h
@brief �摜�f�[�^�N���X���Ǘ����A�X�N���[����ɕ`�悷��N���X
*/

/*
@brief �C���N���[�h
*/
#include "pch.h"

//UI��ID�A�J�E���g�p�̏�����
int UIComponent::mUIid = 0;

/*
@fn	   �R���X�g���N�^
@param _owner �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
@param _drawOrder �`��̏��ԁi���l���������قǑ����`�悳���j
*/
UIComponent::UIComponent(GameObject* _owner, int _drawOrder)
	: Component(_owner)
	, mTexture(nullptr)
	, mDrawOrder(_drawOrder)
	, mTextureWidth(0)
	, mTextureHeight(0)
	, mVisible(true)
	, mMyUIid(mUIid)
{
	mUIid++;
	//�����_���[�Ƀ|�C���^�[�𑗂�
	RENDERER->AddUI(this);
}

/*
@fn	�f�X�g���N�^
*/
UIComponent::~UIComponent()
{
	mUIid--;
	//�����_���[����|�C���^���폜����
	RENDERER->RemoveUI(this);
}

/*
@fn		�`�揈��
@param	_shader �g�p����V�F�[�_�[�N���X�̃|�C���^
*/
void UIComponent::Draw(Shader* _shader, const Vector3& _Offset)
{
	//�摜��񂪋�łȂ����A�e�I�u�W�F�N�g�����X�V��ԂłȂ���
	if (mTexture && mOwner->GetState() != State::Dead)
	{
		Matrix4 scaleMatrix = Matrix4::CreateScale(
			static_cast<float>(mTextureWidth),
			static_cast<float>(mTextureHeight),
			1.0f);

		// �X�N���[���ʒu�̕��s�ړ�
		Matrix4 transMat = Matrix4::CreateTranslation(
			Vector3(_Offset.x - (mTextureWidth * 0.0f),
				(mTextureHeight * 0.0f) - _Offset.z, 0.0f));

		Matrix4 world = scaleMatrix * transMat;

		_shader->SetMatrixUniform("uWorldTransform", world);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mTexture->GetTextureID());
		_shader->SetIntUniform("uSpriteTexture", 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	}
}

/*
@fn		�e�N�X�`�����Z�b�g���c���̒������v�Z����
@param	_texture �g�p����e�N�X�`���̃|�C���^
*/
void UIComponent::SetTexture(Texture* _texture)
{
	mTexture = _texture;
	mTextureWidth = mTexture->GetWidth();
	mTextureHeight = mTexture->GetHeight();
}
