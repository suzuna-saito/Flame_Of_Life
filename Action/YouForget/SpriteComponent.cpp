/*
@file	SpriteComponent.h
@brief	�摜�f�[�^�N���X���Ǘ����A�X�N���[����ɕ`�悷��N���X
*/

/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_owner �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
@param	_drawOrder �`��̏��ԁi���l���������قǑ����`�悳���j
*/
SpriteComponent::SpriteComponent(GameObject* _owner, int _drawOrder)
	: Component(_owner)
	, mTexture(nullptr)
	, mDrawOrder(_drawOrder)
	, mTextureWidth(0)
	, mTextureHeight(0)
	, mVisible(true)
{
	//�����_���[�Ƀ|�C���^�[�𑗂�
	RENDERER->AddSprite(this);
}

/*
@fn		�f�X�g���N�^
*/
SpriteComponent::~SpriteComponent()
{
	//�����_���[����|�C���^���폜����
	RENDERER->RemoveSprite(this);
}

/*
@brief	�`�揈��
@param _shader �g�p����V�F�[�_�[�N���X�̃|�C���^
*/
void SpriteComponent::Draw(Shader* _shader)
{
	//�摜��񂪋�łȂ����A�e�I�u�W�F�N�g�����X�V��ԂłȂ���
	if (mTexture && mOwner->GetState() != State::Dead)
	{
		Matrix4 scaleMatrix = Matrix4::CreateScale(
			static_cast<float>(mTextureWidth),
			static_cast<float>(mTextureHeight),
			1.0f);

		Matrix4 world = scaleMatrix * mOwner->GetWorldTransform();

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
void SpriteComponent::SetTexture(Texture* _texture)
{
	mTexture = _texture;
	mTextureWidth = mTexture->GetWidth();
	mTextureHeight = mTexture->GetHeight();
}
