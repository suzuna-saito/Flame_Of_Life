#include "pch.h"

CircledShadow::CircledShadow(class GameObject* _owner)
	: ParticleEffectBase()
	, MBaseZPos(90.0f)
	, MMaxScale(300.0f)
	, MAddAlpha(0.03f)
	, MSubAlpha(-0.07f)
{
	// �e�N�X�`�����Z�b�g
	mParticle->SetTextureID(RENDERER->GetTexture("Assets/Effect/Particle.png")->GetTextureID());
	// ��Z����F��ݒ�
	mParticle->SetColor(Color::LightPink);
	// ��]�l��ݒ�
	mParticle->SetAngle(Vector3(0.5f, 0.0f, 0.0f));
	// �u�����h�̎�ނ����u�����h�ɐݒ�
	mParticle->SetBlendMode(ParticleComponent::ParticleBlendType::eAlphaBlend);
	
	// GameObject�N���X�̕ϐ�������
	mPosition = _owner->GetPosition();		// �|�W�V����
	mPosition.z = MBaseZPos;
	mScale = Vector3(MMaxScale,0.0f,0.0f);	// �X�P�[��
	mMoveSpeed = 1.15f;						// �l�̕ω��l

	// �A�^�b�`�����I�u�W�F�N�g�̃|�C���^
	mOwner = _owner;
}

void CircledShadow::UpdateGameObject(float _deltaTime)
{
	// �|�W�V�������X�V
	mPosition = mOwner->GetPosition();

	// �A�^�b�`�����I�u�W�F�N�g�̃|�W�V������90.0f�ȏ�̎�
	if (mOwner->GetPosition().z >= MBaseZPos)
	{
		// ���l��1.0f������������
		if (mAlpha < 1.0f)
		{
			// ���l��ύX
			mAlpha += MAddAlpha;
		}

		// �|�W�V����Z��90.0f�ɐݒ�
		mPosition.z = MBaseZPos;
		// �X�P�[�����X�V
		mScale.x = MMaxScale - mOwner->GetPosition().z / 4;// MMaxScale - �A�^�b�`�����I�u�W�F�N�g�̃|�W�V����/4
	}
	// �A�^�b�`�����I�u�W�F�N�g�̃|�W�V������90.0f�����̎�
	else
	{
		// ���l��0.0f���ゾ������
		if (mAlpha > 0.0f)
		{
			// ���l��ύX
			mAlpha += MSubAlpha;
		}
	}
}