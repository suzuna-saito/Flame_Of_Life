/*
@brief	�v���v���Z�b�T
*/
#pragma once

/*
@brief �O���錾
*/
class Jump;
class LegsCollider;
class FallEffectManager;

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

	// ���A�ʒu��ݒ�
	void SetReturnPos(Vector3 _returnPos) { mReturnPos = _returnPos; }

	// �v���C���[������\��Ԃ� true _�\�@false _�s�\
	static bool mOperable;
private:
	// �v���C���[�̍s���̏��
	typedef enum class playerState :unsigned char
	{
		idle,         // �ҋ@
		run,          // ����

		stateNum           // state_num�@�K���Ō�ɏ���
							// �X�e�[�g�̌�
	}playerState;


	/*
	@fn		��`�Ƌ�`�̉����߂�
	@param	_myAABB	��ɂ���I�u�W�F�N�g�̋�`�����蔻��
	@param	_pairAABB �q�b�g����I�u�W�F�N�g�̋�`�����蔻��
	@param	_pairTag �q�b�g����I�u�W�F�N�g�̃^�O
	*/
	void FixCollision(const AABB& _myAABB, const AABB& _pairAABB, const Tag& _pairTag)override;

	
	//�v���C���[�̓����蔻��𐶐�
	BoxCollider* mSelfBoxCollider;
	//�X�P���^�����b�V��
	SkeletalMeshComponent* mSkelComp;
	
	// �G�t�F�N�g
	//�v���C���[�����������̃G�t�F�N�g
	FallEffectManager* mFallEffectManager;


	// ���݂̏��
	playerState  mNowState;
	// 1�O�̏��
	playerState  mPrevState;

	// �A�j���[�V����
	vector<const class Animation*> mAnimations;
	// ��]�ڕW����
	Vector3 mAnimVec; 

	// �v���C���[�̕��A�|�W�V����
	Vector3 mReturnPos;
	// �������Ƃ��ɕۊǂ��鎟�̃|�W�V����
	Vector3 mDifference;

	// �J�����|�W�V����
	Vector3 mCameraPos;
	// �J������Z�������_
	const float MCameraPointZ;
	// �Q�[�����X�^�[�g����J�����̈ʒu
	const float MStartCameraPos;
	// �J���������̍����ɍs���܂ő����l
	const float MAddCameraPos;
	// �J�������v���C���[��ǂ��悤�ɂȂ�v���C���[�̂����̍���
	const float MChagePosZ;

	// �v���C���[�̃��X�|�[������^�C�~���O����
	const float MRedoingPosZ;
	// ���X�|�[���ʒu��������������
	float MReturnAddZ;
	// ���X�|�[�����̑��x
	const float MRedoingSpeedZ;

	// �W�����v���̍ő�Velocity
	const float MMaxJumpVel;

	// �Q�[�����X�^�[�g�������ǂ���
	bool mStartFlag;

	// �U�������邩�ǂ���
	bool mVibrationFlag;

	// �W�����v
	Jump* mJump;

	// �����p�̓����蔻��
	LegsCollider* mLegs;

	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�(��������p)
	@param	��������GameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;

	/*
	@fn		�v���C���[���������ۂ̏���
	@param	_nowPos	���݂̃|�W�V����
	@param	_returnPos ���A�ʒu
	*/
	void mRedoing(Vector3 _nowPos, const Vector3 _returnPos);
	
	
	// �A�j���[�V�����֌W
	
	// �A�C�h�����
	void mIdleBehavior();
	// �������
	void mRunBehavior();


////�f�o�b�N�p
//	Vector3 testPos;
	bool mDebug;

public:
	// �Q�[�����X�^�[�g���Ă邩�ǂ���
	bool GetStartFlag() { return mStartFlag; }
};

