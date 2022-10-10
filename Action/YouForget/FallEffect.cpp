#include "pch.h"

FallEffect::FallEffect(class GameObject* _owner)
	:ParticleEffectBase(_owner)
	, MBaseScale(200.0f)
	, MAddScale(10.0f)
	, MSubAlpha(-0.03f)
	, mTmpVisible(false)
{
	// �e�N�X�`�����Z�b�g
	mParticle->SetTextureID(RENDERER->GetTexture("Assets/Effect/Ripple.png")->GetTextureID());
	// ��Z����F��ݒ�
	mParticle->SetColor(Color::Red);
	// ��]�l��ݒ�
	mParticle->SetAngle(Vector3(0.5f, 0.0, 0.0f));
	// �u�����h�̎�ނ����u�����h�ɐݒ�
	mParticle->SetBlendMode(ParticleComponent::ParticleBlendType::eAlphaBlend);
	// �`������邩�ǂ�����ݒ�
	mParticle->SetVisible(false);
	
	// GameObject�N���X�̕ϐ�������
	mScale = Vector3(MBaseScale, 1.0f, 1.0f);	// �X�P�[��
}

void FallEffect::UpdateGameObject(float _deltaTime)
{
	// �`��t���O���O������ύX���ꂽ��
	if (mTmpVisible != mParticle->GetVisible())
	{
		// �`��|�W�V�������X�V
		mPosition = mOwner->GetPosition();
	}

	// ���l��0.0f�ȉ���������
	if (mAlpha <= 0.0f)
	{
		// ���l�A�X�P�[���������l�ɖ߂�
		mAlpha = 1.0f;			// ���l
		mScale.x = MBaseScale;	// �X�P�[��

		// �`��t���O��false�ɂ���
		mParticle->SetVisible(false);
	}

	// �`��t���O��true��������
	if (mParticle->GetVisible())
	{
		// ���l�A�X�P�[�����X�V
		mAlpha += MSubAlpha;	// ���l
		mScale.x += MAddScale;	// �X�P�[��
	}

	// �`�悵�Ă������ǂ�����ۑ�
	mTmpVisible = mParticle->GetVisible();
}