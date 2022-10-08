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
UIComponent::UIComponent(GameObject* _owner, const Vector3 _pos, const Vector3 _scale, int _drawOrder)
	: Component(_owner)
	, mTexture(nullptr)
	, mDrawOrder(_drawOrder)
	, mTextureWidth(0)
	, mTextureHeight(0)
	, mVisible(true)
	, mMyUIid(mUIid)
	, mScale(_scale)
	, mPos(_pos)
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
void UIComponent::Draw(Shader* _shader, const Vector3& _Pos, const Vector3 _scale)
{
	//�摜��񂪋�łȂ����A�e�I�u�W�F�N�g�����X�V��ԂłȂ���
	if (mTexture && mOwner->GetState() != State::Dead)
	{
		Matrix4 scaleMatrix = Matrix4::CreateScale(
			static_cast<float>(mTextureWidth)* _scale.x,
			static_cast<float>(mTextureHeight)* _scale.y,
			1.0f);

		// �X�N���[���ʒu�̕��s�ړ�
		Matrix4 transMat = Matrix4::CreateTranslation(
			Vector3(_Pos.x - (mTextureWidth * 0.0f),
				_Pos.y - (mTextureHeight * 0.0f), 0.0f));

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
