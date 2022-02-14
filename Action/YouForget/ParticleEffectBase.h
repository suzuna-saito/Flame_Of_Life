/*
@file ParticleEffectBase.h
@brief ��莞�Ԃŏ�����A��ɃG�t�F�N�g�̊��N���X�Ƃ��Ďg�p�����N���X
*/

/*
@brief	�v���v���Z�b�T
*/
#pragma once


/*
@enum	�p�[�e�B�N���̏��
*/
enum class ParticleState :unsigned char
{
	//�A�N�e�B�u
	PARTICLE_ACTIVE,
	//�����ɂ���
	PARTICLE_DISABLE,
};

class ParticleEffectBase : public GameObject
{
public:

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
	ParticleEffectBase(const Vector3& _pos, const Vector3& _vel, const int& _lifeCount, const std::string& _particleFileName, SceneBase::Scene _sceneTag, const Tag& _objectTag , bool _billFlag ,const float& _scale = 10);

	/*
	@fn	�f�X�g���N�^
	*/
	virtual ~ParticleEffectBase() {};

	/*
	@fn		�h���N���X�̍X�V�֐����Ăэ��W�Ɉړ��ʂ𑫂�������
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

protected:

	/*
	@fn �������Ԃ��J�E���g�_�E������֐��B�h���N���X�ōX�V�֐������肵���ꍇ�����ɒǉ����邱�ƁB
	*/
	void LifeCountDown();

	//�p�[�e�B�N���̕`��N���X
	ParticleComponent* mParticle;

	//��������
	int					mLifeCount;

	//�A���t�@�l
	float				mAlpha;
	//�傫��
	float				mScale;
	//�����x
	float				mSpeed;

public:

	/*
	@param _flag ���]���s����
	*/
	void SetReverve(float _flag);
};
