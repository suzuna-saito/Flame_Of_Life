/*
@brief	�v���v���Z�b�T
*/
#pragma once

class Ground :public GameObject
{
public:

	// ���̎��
	enum class groundTag :unsigned char
	{
		// �����ɂȂ�i����y�j
		RGBalpha,
		// �����ɂȂ�i�Œ�̐F�j
		alpha,
		// �����ɂȂ�Ȃ�
		notAlpha,
	};

	// ���l�̕ς�鏰�̐F
	enum class alphaColor :unsigned char
	{
		red,
		green,
		yellow
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

	// �V�[���ɂ���ď��̐F�̎�ނ̐����قȂ�
	static int mTypeNum;

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

	// ���l�̕ς����
	int mAlphaNum;
	
	// ���l�̕ς���Ă������x
	const float MAlphaAddSpeed;
	const float MAlphaSubSpeed;

	// ���l�̍ő�l
	float MAlphaMax;
	// ���l�̍ŏ��l
	float MAlphaMin;

	// ������ʂ�̂͏��߂Ă� true: ���߂�
	bool mFirstFlag;

	// ���̎��
	groundTag mGroundTag;

	// ���̐F�̎��
	alphaColor mAlphaColorTag;

	/*
	@fn		���̐F�A���l�̕ς��^�C�~���O��ݒ肷��
	*/
	void mInit();

};

