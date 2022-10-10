#include "pch.h"

CircledShadow::CircledShadow(class GameObject* _owner, const Vector3 _color)
	: ParticleEffectBase(_owner)
	, MBaseZPos(90.0f)
	, MMaxScale(350.0f)
	, MInitOwnerAlpha(mOwner->GetAlpha())
	, MMaxAlpha(0.8f)
	, MAddAlpha(0.02f)
	, MSubAlpha(-0.03f)
{
	// �e�N�X�`�����Z�b�g
	mParticle->SetTextureID(RENDERER->GetTexture("Assets/Effect/Particle.png")->GetTextureID());
	// ��]�l��ݒ�
	mParticle->SetAngle(Vector3(0.5f, 0.0f, 0.0f));
	// �u�����h�̎�ނ����u�����h�ɐݒ�
	mParticle->SetBlendMode(ParticleComponent::ParticleBlendType::eAlphaBlend);
	
	// GameObject�N���X�̕ϐ�������
	mPosition = _owner->GetPosition();				// �|�W�V����
	mPosition.z = MBaseZPos;
	mScale = Vector3(MMaxScale, 1.0f, MMaxScale);	// �X�P�[��
	mColor = _color;								// ��Z����F
	mAlpha = MMaxAlpha;								// ���l
}

void CircledShadow::UpdateGameObject(float _deltaTime)
{
	// �|�W�V�������X�V
	mPosition = mOwner->GetPosition();

	// �A�^�b�`�����I�u�W�F�N�g�̃|�W�V������90.0f�����̎��A
	// �܂��̓A�^�b�`�����I�u�W�F�N�g�̃X�e�[�^�X���A�N�e�B�u����Ȃ�������
	if (mOwner->GetPosition().z < MBaseZPos || mOwner->GetState() != State::Active)
	{
		// ���l��0.0f���ゾ������
		if (mAlpha > 0.0f)
		{
			mAlpha += MSubAlpha;	// ���l���X�V
		}
	}
	// ��L�̏�������v���Ȃ������Ƃ�
	else
	{
		// �A�^�b�`�����I�u�W�F�N�g�̃��l���X�V����Ă�����
		if (MInitOwnerAlpha != mOwner->GetAlpha())
		{
			// ���l���A�^�b�`�����I�u�W�F�N�g�̃��l�ɍ��킹�čX�V
			mAlpha = mOwner->GetAlpha() - (MInitOwnerAlpha - MMaxAlpha);
		}
		// ���l��MMaxAlpha������������
		else if (mAlpha < MMaxAlpha)
		{
			mAlpha += MAddAlpha;	// ���l���X�V
		}

		// �|�W�V�����A�X�P�[�����X�V
		mPosition.z = MBaseZPos;								//�|�W�V����Z��MBaseZPos�ɐݒ�
		mFloatScale = MMaxScale - mOwner->GetPosition().z / 4;	// MMaxScale - �A�^�b�`�����I�u�W�F�N�g�̃|�W�V����/4
		mScale = Vector3(mFloatScale, 1.0f, mFloatScale);
	}
}