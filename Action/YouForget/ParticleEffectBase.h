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

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner">�A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^</param>
	ParticleEffectBase(class GameObject* _owner);
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

	class GameObject* mOwner;	// �A�^�b�`�����I�u�W�F�N�g�̃|�C���^
public:
	/*
	@param _flag ���]���s����
	*/
	void SetReverve(float _flag);

	// �摜��`�悷�邩���Ȃ����Z�b�g���� true:�`�悷��
	void SetThisVisible(bool _flag) { mParticle->SetVisible(_flag); }
};