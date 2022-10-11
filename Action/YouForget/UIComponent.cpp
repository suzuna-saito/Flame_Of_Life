#include "pch.h"

UIComponent::UIComponent(class GameObject* _owner, const int _drawOrder)
	: Component(_owner)
	, mDrawOrder(_drawOrder)
	, mTexture(nullptr)
	, mTextureWidth(0)
	, mTextureHeight(0)
	, mVisible(true)
{
	//�����_���[�Ƀ|�C���^�[�𑗂�
	RENDERER->AddUI(this);
}

UIComponent::~UIComponent()
{
	//�����_���[����|�C���^���폜����
	RENDERER->RemoveUI(this);
}

void UIComponent::Draw(Shader* _shader)
{
	// �摜��񂪋󂶂�Ȃ����A�I�u�W�F�N�g�����X�V��Ԃ���Ȃ�������
	if (mTexture && mOwner->GetState() != State::Dead)
	{
		// �X�P�[���̍X�V
		Matrix4 scaleMatrix = Matrix4::CreateScale(
			static_cast<float>(mTextureWidth)* mOwner->GetScale().x,
			static_cast<float>(mTextureHeight)* mOwner->GetScale().y,
			1.0f);

		// �X�N���[���ʒu�̕��s�ړ�
		Matrix4 transMat = Matrix4::CreateTranslation(
			Vector3(mOwner->GetPosition().x - (mTextureWidth * 0.0f),
				mOwner->GetPosition().y - (mTextureHeight * 0.0f),
				0.0f));

		// �s����v�Z
		Matrix4 world = scaleMatrix * transMat;
		// uWorldTransform��ݒ�
		_shader->SetMatrixUniform("uWorldTransform", world);
		// uAlpha��ݒ�
		_shader->SetFloatUniform("uAlpha", mOwner->GetAlpha());

		// ���ꂩ��X���b�g���hGL_TEXTURE0���̐ݒ������
		glActiveTexture(GL_TEXTURE0);
		// �e�N�X�`���̊��蓖��
		glBindTexture(GL_TEXTURE_2D, mTexture->GetTextureID());
		// �`��
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}

void UIComponent::SetTexture(Texture* _texture)
{
	// �e�N�X�`�����Z�b�g
	mTexture = _texture;
	// �c�A���̒������擾
	mTextureWidth = mTexture->GetWidth();
	mTextureHeight = mTexture->GetHeight();
}
