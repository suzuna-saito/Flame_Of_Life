/*
@brief	�v���v���Z�b�T
*/
#pragma once

class Ground :public GameObject
{
public:
	/*
	@fn		�R���X�g���N�^
	@param	_pos �|�W�V����
	@param	_size �T�C�Y
	@param	_objectTag �I�u�W�F�N�g�̃^�O
	@param	_sceneTag �V�[���^�O
	@param	_alphaFlag �����ɂ��鏰���ǂ��� true: �����ɂ��� false: �����ɂ��Ȃ�
	*/
	Ground(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag, const bool _alphaFlag);

	// �f�X�g���N�^
	~Ground() {};

	/*
	@fn		���̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
	//�Q�[���I�u�W�F�N�g�̃��b�V���|�C���^�ϐ�
	MeshComponent* mMeshComponent;

	// �l�p�̒n�ʂ̓����蔻��𐶐�
	BoxCollider* mSelfBoxCollider;

	// ���l�̕ς��^�C�~���O���&���̐F
	enum Alpha
	{
		red,
		green,
		blue
	};

	// ���l�̕ς��^�C�~���O���
	int mAlphaNum;
	// ���l�̕ς��^�C�~���O
	int mAlphaTiming;
	// ���l�̕ς��J�E���g
	int mCount;

	const int MTwoTime;
	const int MThreeTime;

	// ���l�̍ő�l
	float MAlphaMax;
	// ���l�̍ŏ��l
	float MAlphaMin;
	// ���l�̕ς�鑬�x
	float MAlphaValue;

	// ���̓����x���オ�邩�����邩 true: �オ�� false: ������
	bool mAlphaChange;
	// �����ɂȂ鏰���ǂ���
	bool mAlphaGround;
	// ������ʂ�̂͏��߂Ă� true: ���߂�
	bool mFirstFlag;

	/*
	@fn		���̐F�A���l�̕ς��^�C�~���O��ݒ肷��
	*/
	void mInit();
};

