#include "pch.h"

FallEffect::FallEffect(class GameObject* _owner)
	:ParticleEffectBase(_owner)
	, MBaseScale(200.0f)
	, MAddScale(10.0f)
	, MSubAlpha(-0.03f)
	, mTmpVisible(false)
{
	// �e�N�X�`�����Z�b�g
	mParticle->SetTexture(RENDERER->GetTexture("Assets/Effect/Ripple.png"));
	// ��]�l��ݒ�
	mParticle->SetAngle(Vector3(0.5f, 0.0, 0.0f));
	// �u�����h�̎�ނ����u�����h�ɐݒ�
	mParticle->SetBlendMode(ParticleComponent::ParticleBlendType::eAlphaBlend);
	// �`������邩�ǂ�����ݒ�
	mParticle->SetVisible(false);
	
	// �X�P�[���l��float�l����
	mFloatScale = MBaseScale;

	// GameObject�N���X�̕ϐ�������
	mScale = Vector3(MBaseScale, 1.0f, MBaseScale);	// �X�P�[��
	mColor = Color::Red;							// ��Z����F
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
		mAlpha = 1.0f;				// ���l
		mFloatScale = MBaseScale;	// �X�P�[��

		// �`��t���O��false�ɂ���
		mParticle->SetVisible(false);
	}

	// �`��t���O��true��������
	if (mParticle->GetVisible())
	{
		// ���l�A�X�P�[�����X�V
		mAlpha += MSubAlpha;		// ���l
		mFloatScale += MAddScale;	// �X�P�[��
	}

	// �X�P�[�����X�V
	mScale = Vector3(mFloatScale, 1.0f, mFloatScale);
	// �`�悵�Ă������ǂ�����ۑ�
	mTmpVisible = mParticle->GetVisible();
}