/*
@file ParticleEffectBase.h
@brief ��莞�Ԃŏ�����A��ɃG�t�F�N�g�̊��N���X�Ƃ��Ďg�p�����N���X
*/

/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_pos �G�t�F�N�g�̐����ꏊ
@param	_vel �G�t�F�N�g�̑��x
@param	_lifeCount �G�t�F�N�g�̐�������
@param	_particleFileName �摜�ւ̃A�h���X
@param	_objectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
@param	_sceneTag �V�[���̃^�O
@param	_scale �摜�̊g��T�C�Y
*/
ParticleEffectBase::ParticleEffectBase(const Vector3& _pos, const Vector3& _vel, const int& _lifeCount, const std::string& _particleFileName, SceneBase::Scene _sceneTag, const Tag& _objectTag, bool _billFlag, const float& _scale)
	: GameObject(_sceneTag, _objectTag)
	, mLifeCount(_lifeCount)
	, mAngle(Vector3::Zero)
	, mAlpha(0.0f)
	, mScale(0.0f)
	, mSpeed(0.0f)
	/*, mParticleState(ParticleState::PARTICLE_ACTIVE)*/
{
	mVelocity = _vel;
	mParticle = new ParticleComponent(this, _billFlag);
	mParticle->SetTextureID(RENDERER->GetTexture(_particleFileName)->GetTextureID());
	mParticle->SetColor(Vector3(1.0f, 1.0f, 1.0f));
	mParticle->SetScale(_scale);
	SetPosition(_pos);
}

/*
@fn		�h���N���X�̍X�V�֐����Ăэ��W�Ɉړ��ʂ𑫂�������
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void ParticleEffectBase::UpdateGameObject(float _deltaTime)
{
	LifeCountDown();
	SetPosition(mPosition + mVelocity);
}

/*
@fn �������Ԃ��J�E���g�_�E������֐��B�h���N���X�ōX�V�֐������肵���ꍇ�����ɒǉ����邱�ƁB
*/
void ParticleEffectBase::LifeCountDown()
{
	//�������Ԃ��[���ɂȂ�Ƃ��̃I�u�W�F�N�g���X�V�I������
	if (mLifeCount <= 0)
	{
		mParticle->SetVisible(false);
		SetState(State::Dead);
	}
	else
	{
		mParticle->SetVisible(true);
		mLifeCount--;
	}

}

/*
@param _flag ���]���s����
*/
void ParticleEffectBase::SetReverve(float _flag)
{
	mParticle->SetReverce(_flag);
}