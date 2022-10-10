#include "pch.h"

GoalEffect::GoalEffect(class GameObject* _owner)
	: ParticleEffectBase(_owner)
	, MAddAngleY(0.002f)
	, MMInAlpha(0.6f)
	, mAddScale(1.5f)
	, mAddAlpha(0.005f)
{
	// �e�N�X�`�����Z�b�g
	mParticle->SetTextureID(RENDERER->GetTexture("Assets/Effect/Goal.png")->GetTextureID());
	// �u�����h�̎�ނ����u�����h�ɐݒ�
	mParticle->SetBlendMode(ParticleComponent::ParticleBlendType::eAlphaBlend);
	
	// GameObject�N���X�̕ϐ�������
	mPosition = mOwner->GetPosition();		// �|�W�V����
	mScale = Vector3(1000.0f, 1.0f, 1.0f);	// �X�P�[��
}

void GoalEffect::UpdateGameObject(float _deltaTime)
{
	// ���l��1.0f�ȏ�A�܂���0.6f�ȉ��̎�
	if (mAlpha >= 1.0f || mAlpha <= MMInAlpha)
	{
		// �l�̕ω��l�̕����X�V
		mAddAlpha *= -1.0f;
		mAddScale *= -1.0f;
	}

	// �A���O�������]������
	if (mAngle.y >= 2.0f)
	{
		// �����l�ɖ߂�
		mAngle.y = 0.0f;
	}

	// ��]�l�A���l�A�X�P�[���̍X�V
	mAngle.y += MAddAngleY;	// ��]�l
	mAlpha += mAddAlpha;	// ���l
	mScale.x += mAddScale;	// �X�P�[��

	// ��]�l��ݒ�
	mParticle->SetAngle(mAngle);
}