/*
@brief �v���v���Z�b�T
*/
#pragma once

/*
@brief �O���錾
*/
class ItemEffect;
class Item;


class ItemEffectManager : public GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
	@param	_SceneTag �V�[���̃^�O
	@param _ItemPtr �A�C�e���̃|�C���^
	*/
	ItemEffectManager(const Tag& _ObjectTag, const SceneBase::SceneType _SceneTag, Item* _ItemPtr);

	/*
	@fn	�f�X�g���N�^
	*/
	~ItemEffectManager() {};

	/*
	@fn		�G�t�F�N�g�}�l�[�W���[�̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	/*
	@brief �A�C�e���G�t�F�N�g�̕���
	*/
	enum class DirectionItemEffect :unsigned char
	{
		eLeftDeath,
		eBackDeath,
		eLeftBackDeath
	};


	/*
	@fn    ���x�����߂�
	@param _Quantity ��
	*/
	void DecideVelocity(const int _Quantity);

	//�Q�[���I�u�W�F�N�g�N���X�̃|�C���^
	GameObject* mOwner;
	//�p�[�e�B�N���̏��
	ParticleEffectBase::ParticleState mState;
	//�V�[���̃^�O
	SceneBase::SceneType mSceneTag;
	//�A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
	Tag				 mTag;
	//�A�C�e���G�t�F�N�g
	ItemEffect* mItemEffect;
	//�A�C�e���̃|�C���^
	Item* mItem;
	// �����_���̑��x
	Vector3 mRandVel;

	//�C�ӂ̃^�C�~���O�Ńf�X�G�t�F�N�g�𐶐����邽�߂̃J�E���g
	int				 mCreateItemEffectCount;

	//�p�x
	float			 mAngle;

	//�A�C�e���G�t�F�N�g�𐶐����邽�߂̃t���O
	bool			 OneCreateItemFlag;

	bool farstFlag;
	

};

