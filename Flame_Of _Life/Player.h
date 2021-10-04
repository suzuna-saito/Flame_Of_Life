/*
@brief	�v���v���Z�b�T
*/
#pragma once


class Player :public GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_pos �v���C���[�̍��W
	@param	_size �v���C���[�̃T�C�Y
	@param	_objectTag �v���C���[�̃^�O
	@param	_sceneTag �V�[���̃^�O
	*/
	Player(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	/*
	@fn	�f�X�g���N�^
	*/
	~Player() {};

	/*
	@fn		�v���C���[�̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

	/*
	@fn		���͂������Ŏ󂯎��X�V�֐�
	@brief	��{�I�ɂ����œ��͏���ϐ��ɕۑ���UpdateGameObject�ōX�V���s��
	@param	_keyState �e���͋@��̓��͏��
	@brief	�L�[�{�[�h�A�}�E�X�A�R���g���[���[
	*/
	void GameObjectInput(const InputState& _keyState)override;

private:

	//�Q�[���I�u�W�F�N�g�̃��b�V���|�C���^�ϐ�
	MeshComponent* mMeshComponent;
	//�v���C���[�̋������蔻��𐶐�
	//SphereCollider*		mSelfSphereCollider;
	BoxCollider* mSelfBoxCollider;

	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�(��������p)
	@param	��������GameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;


	// �d��
	static const float Gravity;

	// �ړ��X�s�[�h
	const float mMoveSpeed;

	// �n�ʂɐڒn���Ă���ǂ���
	bool mIsGroundFlag;

	// �ŏ��̃W�����v��
	const float mAccelerator;
	// �W�����v��
	const float mJump;
	// �ő�W�����v��
	const float mMaxJump;
	// �W�����v�����ǂ���
	bool mNowJump;

public://�Q�b�^�[�Z�b�^�[

};

