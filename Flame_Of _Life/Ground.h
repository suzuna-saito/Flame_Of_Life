/*
@brief	�v���v���Z�b�T
*/
#pragma once

class Ground :public GameObject
{
public:

	// ���̎��
	enum groundTag
	{
		// �����ɂȂ�i�������j
		RGBalpha,
		// �����ɂȂ�i�Œ�̐F�j
		alpha,
		// �����ɂȂ�Ȃ�
		notAlpha,
		// �����Ԃ���������鏰
		stayAlpha
	};

	/*
	@fn		�R���X�g���N�^
	@param	_pos �|�W�V����
	@param	_size �T�C�Y
	@param	_objectTag �I�u�W�F�N�g�̃^�O
	@param	_sceneTag �V�[���^�O
	@param	_tag ���̎��
	*/
	Ground(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag,const groundTag& _tag);

	// �f�X�g���N�^
	~Ground() {};

	/*
	@fn		���̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�(��������p)
	@param	��������GameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;

	//�Q�[���I�u�W�F�N�g�̃��b�V���|�C���^�ϐ�
	MeshComponent* mMeshComponent;

	// �l�p�̒n�ʂ̓����蔻��𐶐�
	BoxCollider* mSelfBoxCollider;

	// ���l�̕ς��^�C�~���O���&���̐F
	enum alphaColor
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
	// �Ԃ̏��̐F���ς��^�C�~���O
	const int MRedTime;
	// �΂̏��̐F���ς��^�C�~���O
	const int MGreenTime;
	// �̏��̐F���ς��^�C�~���O
	const int MBlueTime;

	// ���l�̍ő�l
	float MAlphaMax;
	// ���l�̍ŏ��l
	float MAlphaMin;
	// ���l�̕ς�鑬�x
	float MAlphaValue;

	// ���̓����x���オ�邩�����邩 true: �オ�� false: ������
	bool mAlphaChange;
	// ������ʂ�̂͏��߂Ă� true: ���߂�
	bool mFirstFlag;
	// �v���C���[�Ɠ������Ă��邩�ǂ���
	bool mStayPlayer;

	// ���̎��
	groundTag mGroundTag;

	/*
	@fn		���̐F�A���l�̕ς��^�C�~���O��ݒ肷��
	*/
	void mInit();

};

