/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_Pos �A�C�e���G�t�F�N�g�̐����ꏊ
@param	_Vel �A�C�e���G�t�F�N�g�̑��x
@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
@param	_SceneTag �V�[���̃^�O
*/
ItemEffect::ItemEffect(const Vector3 _Pos, const Vector3 _Vel, const Tag& _ObjectTag, const SceneBase::SceneType _SceneTag, Item* _ItemPtr)
	:ParticleEffectBase()
	, mItemVisible(true)
{
	// �e�N�X�`�����Z�b�g
	mParticle->SetTextureID(RENDERER->GetTexture("Assets/Effect/Particle.png")->GetTextureID());

	mAngle.x = 0.5f;
	mAlpha = 0.7f;
	mScale = Vector3(500.0f, 1.0f, 1.0f);
	mParticle->SetAngle(mAngle);
	mParticle->SetAlpha(mAlpha);
	mParticle->SetColor(Color::White);
	mParticle->SetBlendMode(ParticleComponent::ParticleBlendType::eAlphaBlend);
	mVelocity = _Vel;
	mMoveSpeed = 1.15f;

	mItem = _ItemPtr;
}

/*
@fn		�f�X�G�t�F�N�g�̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void ItemEffect::UpdateGameObject(float _deltaTime)
{

	//�A���t�@�l�̍팸�l
	const float AlphaReductionVal = 0.02f;
	////�X�P�[���̒ǉ��l
	//const float ScaleAddVal = 1.0f;

	//if(mAlpha>0.)

	//�A�C�e�������݂��ĂȂ������猩���Ȃ�����
	if (!mItem->mGetItemExistsFlag())
	{
		if (mAlpha >= 0.0f)
		{
			mAlpha -= AlphaReductionVal;
		}
		else
		{
			mParticle->SetVisible(false);
			mItemVisible = false;
		}
	}
	
	//���C�t�J�E���g��0���傫�������瓧���x�A�X�P�[���̒l���X�V
	mParticle->SetAlpha(mAlpha);
}
