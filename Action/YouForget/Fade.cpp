#include "pch.h"

// �ÓI�����o�ϐ��̏�����
bool Fade::mFadeFlag = false;

Fade::Fade()
	: UIBase()
	, mFadeSpeed(0.01f)
{
	// UIComponent�𐶐����邱�ƂŎ����ŕ`�悳���悤�ɂȂ�
	mUIComponent = new UIComponent(this, eFade);
	// �e�N�X�`�����Z�b�g
	mUIComponent->SetTexture(RENDERER->GetTexture("Assets/UI/Fade/Fade.png"));

	// GameObject�N���X�̕ϐ�������
	mScale = Vector3(1920.0f, 1080.0f, 0.0f);	// �X�P�[��
}

void Fade::UpdateGameObject(float _deltaTime)
{
	// mFadeFlag�t���O��true��������
	if (mFadeFlag)
	{
		// ���l�̍X�V
		mAlpha -= mFadeSpeed;
		// ���l��0.0f�ȉ��A��������1.0f�ȏ�ɂȂ�����
		if (mAlpha <= 0.0f || mAlpha >= 1.0f)
		{
			// �t�F�[�h�̍X�V����߂�
			mFadeFlag = false;
		}
	}
}

void Fade::SetFade(Vector3 _color, FadeType _fadeType)
{
	// �F�̐ݒ�
	mColor = _color;

	// �t�F�[�h�C���̎�
	if (_fadeType == FadeType::eIn)
	{
		// ���l : 1.0f
		mAlpha = 1.0f;
		// mFadeSpeed�����̐���������
		if (mFadeSpeed < 0.0f)
		{
			mFadeSpeed *= -1;	// ������ς���
		}
	}
	// �t�F�[�h�A�E�g�̎�
	else
	{
		// ���l : 0.0f
		mAlpha = 0.0f;
		// mFadeSpeed�����̐���������
		if (mFadeSpeed > 0.0f)
		{
			mFadeSpeed *= -1;	// ������ς���
		}
	}

	// �t�F�[�h�̍X�V�������n�߂�
	mFadeFlag = true;
}
