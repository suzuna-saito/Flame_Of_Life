#pragma once

/*
* �G�t�F�N�g�̊��N���X
*/
class ParticleEffectBase : public GameObject
{
public:
	// �p�[�e�B�N���̏��
	enum class ParticleState :unsigned char
	{
		eParticleActive,	// �A�N�e�B�u
		eParticleDisable,	// �����ɂ���
	};

	// �R���X�g���N�^
	ParticleEffectBase();
	// �f�X�g���N�^
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
	// ��]
	Vector3             mAngle;
	//��������
	int					mLifeCount;
public:
	/*
	@param _flag ���]���s����
	*/
	void SetReverve(float _flag);
};