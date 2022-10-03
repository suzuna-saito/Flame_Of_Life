#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_Pos �f�X�G�t�F�N�g�̐����ꏊ
@param	_Vel �N���A�G�t�F�N�g�̑��x
@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
@param	_SceneTag �V�[���̃^�O
*/

FallEffect::FallEffect(const Vector3 _Pos, const Vector3 _Vel, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	:ParticleEffectBase(_Pos, _Vel, 40, "Assets/Effect/Ripple.png", _SceneTag, _ObjectTag,false)
	, MAlphaReductionVal(0.03f)
	, MScaleAddVal(10.0f)
{
	mAngle.x = 0.5f;
	mAlpha = 1.0f;
	mScale = 200.0f;
	mParticle->SetAngle(mAngle);
	mParticle->SetAlpha(mAlpha);
	mParticle->SetScale(mScale);
	//mParticle->SetColor(Color::LightBlue);
	mParticle->SetColor(Color::Red);
	mParticle->SetBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ALPHA);
	mVelocity = _Vel;
}

/*
@fn		�f�X�G�t�F�N�g�̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void FallEffect::UpdateGameObject(float _deltaTime)
{
	//�������Ԃ��J�E���g
	ParticleEffectBase::LifeCountDown();

	//���C�t�J�E���g��0���傫�������瑬�x�A�����x�A�X�P�[���̒l���X�V
	if (mLifeCount > 0)
	{
		mAlpha -= MAlphaReductionVal;
		mScale += MScaleAddVal;

		mParticle->SetAlpha(mAlpha);
		mParticle->SetScale(mScale);
	}

	//���C�t�J�E���g��0�ȉ��������猩���Ȃ�����
	if (mAlpha <= 0.0f)
	{
		mParticle->SetVisible(false);
	}
}
