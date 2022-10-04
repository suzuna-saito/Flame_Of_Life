#pragma once

/*
@brief �v���v���Z�b�T
*/
#pragma once

/*
@brief �O���錾
*/
class FallEffect;
class Player;

///*
//@brief �f�X�G�t�F�N�g�̕���
//*/
//enum DirectionDeathEffect
//{
//	eLeftDeath = 0,
//	eBackDeath = 1,
//	eLeftBackDeath = 2
//};

class FallEffectManager : public GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
	@param	_SceneTag �V�[���̃^�O
	@param _playerPtr �v���C���[�̃|�C���^
	*/
	FallEffectManager(const Tag& _ObjectTag, const SceneBase::SceneType _SceneTag, Player* _playerPtr);

	/*
	@fn	�f�X�g���N�^
	*/
	~FallEffectManager() {};

	/*
	@fn		�G�t�F�N�g�}�l�[�W���[�̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:


	/*
	@fn    ���x�����߂�
	@param _Quantity ��
	*/
	void DecideVelocity(const int _Quantity);

	//�Q�[���I�u�W�F�N�g�N���X�̃|�C���^
	GameObject* mOwner;
	//�p�[�e�B�N���̏��
	ParticleState	 mState;
	//�V�[���̃^�O
	SceneBase::SceneType mSceneTag;
	//�A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
	Tag				 mTag;
	//�f�X�G�t�F�N�g
	FallEffect* mFallEffect;
	//�v���C���[�̃|�C���^
	Player* mPlayer;
	// �����_���̑��x
	Vector3 mRandVel;

	//�C�ӂ̃^�C�~���O�ŗ��������̃G�t�F�N�g�𐶐����邽�߂̃J�E���g
	int				 mCreateFallEffectCount;

	//�p�x
	float			 mAngle;

	//���������̃G�t�F�N�g����x�����������邽�߂̃t���O
	bool			 OneCreateFallFlag;
};

