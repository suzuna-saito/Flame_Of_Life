#include "pch.h"

// �ÓI�����o�ϐ��̏�����
bool Fade::mFadeFlag = false;

Fade::Fade()
	: ParticleEffectBase(nullptr)
	, mFadeSpeed(0.01f)
{
	// �e�N�X�`�����Z�b�g
	mParticle->SetTextureID(RENDERER->GetTexture("Assets/UI/Fade/Fade.png")->GetTextureID());
	// �u�����h�̎�ނ����u�����h�ɐݒ�
	mParticle->SetBlendMode(ParticleComponent::ParticleBlendType::eAlphaBlend);

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
