/*
@brief	�C���N���[�h
*/
#include "pch.h"


/*
@fn		�R���X�g���N�^
@param	_pos �v���C���[�̍��W
@param	_size �v���C���[�̃T�C�Y
@param	_objectTag �v���C���[�̃^�O
@param	_sceneTag �V�[���̃^�O
*/
Player::Player(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, _objectTag)
	, mIsGround(false)
	, MCameraPos(Vector3(0, -700, 200))
	, mMoveSpeed(7.0f)
	, mNowState(IDLE)
	, mPrevState(IDLE)
{
	//GameObject�����o�ϐ��̏�����
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);


	//��������Player�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mSkelComp = new SkeletalMeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mSkelComp->SetMesh(RENDERER->GetMesh("Assets/Player/Human/Player.gpmesh"));

	// �X�P���g���̓ǂݍ���
	mSkelComp->SetSkeleton(RENDERER->GetSkeleton("Assets/Player/Human/Player.gpskel"));

	// �A�j���[�V�����̓ǂݍ���
	mAnimations.resize(STATE_NUM); // �z����m�ہimAnimations��vector�j(STSTE_NUM��enum�̒��̐�)
	mAnimations[IDLE] = RENDERER->GetAnimation("Assets/Player/Human/idle.gpanim");
	mAnimations[RUN] = RENDERER->GetAnimation("Assets/Player/Human/run.gpanim");

	//�A�j���[�V�����̍Đ�
	mSkelComp->PlayAnimation(mAnimations[IDLE]);

	//�v���C���[���g�̓����蔻��(�{�b�N�X)
	mSelfBoxCollider = new BoxCollider(this, ColliderTag::playerTag, GetOnCollisionFunc());
	AABB box = { Vector3(3.0f,-3.0f,0.0f),Vector3(-3.0f,3.0f,35.0f) };
	mSelfBoxCollider->SetObjectBox(box);

	//��]����                        ����]����l
	float radian = Math::ToRadians(90.0f);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::UnitZ, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}

/*
@fn		�v���C���[�̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void Player::UpdateGameObject(float _deltaTime)
{

	//�v���C���[�������낷�ʒu�ɃJ�������Z�b�g
	mMainCamera->SetViewMatrixLerpObject(MCameraPos, mPosition);
	//�v���C���[�������猩��ʒu�ɃJ�������Z�b�g
	//mMainCamera->SetViewMatrixLerpObject(Vector3(300, 0, 200), mPosition);
	// �f�o�b�N�p
	//mMainCamera->SetViewMatrixLerpObject(Vector3(0, -1000, 200), mPosition + testPos);


	// ���݂̏�Ԃ��炻�ꂼ��̂ӂ�܂����s���֐��ɃW�����v
	switch (mNowState)
	{
	case IDLE:
		mIdleBehavior();
		break;

	case RUN:
		mRunBehavior();
		break;

	default:
		break;
	}


	// ���W���Z�b�g
	mPosition += mVelocity;

	// �d��
	if (!mIsGround)
	{
		mPosition.z -= mGravity;
	}

	mIsGround = false;

	// ��Ԃ��؂�ւ������A�j���[�V�������J�n
	if (mNowState != mPrevState)
	{
		mSkelComp->PlayAnimation(mAnimations[mNowState], 0.5f);
	}

	if (!mIsGround)
	{
		ComputeWorldTransform();
	}

	//���̃t���[���̃X�e�[�g��1�O�̃X�e�[�g�ɂȂ�
	mPrevState = mNowState;

	// �|�W�V�������Z�b�g
	SetPosition(mPosition);
}

/*
@fn		���͂������Ŏ󂯎��X�V�֐�
@brief	��{�I�ɂ����œ��͏���ϐ��ɕۑ���UpdateGameObject�ōX�V���s��
@param	_keyState �e���͋@��̓��͏��
@brief	�L�[�{�[�h�A�}�E�X�A�R���g���[���[
*/
void Player::GameObjectInput(const InputState& _keyState)
{
	// �����Ăق��������̃x�N�g��
	Vector3 inputVec = Vector3::Zero;

	// W�ŉ��Ɉړ�
	if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W))
	{
		inputVec.y = 1.0f;
		mVelocity.y = mMoveSpeed;
	}
	// S�Ŏ�O�Ɉړ�
	else if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S))
	{
		inputVec.y = -1.0f;
		mVelocity.y = -mMoveSpeed;
	}
	else
	{
		mVelocity.y = 0.0f;
	}
	// A�ō��Ɉړ�
	if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A))
	{
		inputVec.x = 1.0f;
		mVelocity.x = mMoveSpeed;
	}
	// D�ŉE�Ɉړ�
	else if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D))
	{
		inputVec.x = -1.0f;
		mVelocity.x = -mMoveSpeed;
	}
	else
	{
		mVelocity.x = 0.0f;
	}


	// awsd�̂����ꂩ��������Ă�����
	if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W) || _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S) ||
		_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) || _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D))
	{
		mNowState = RUN;
	}
	else
	{
		mNowState = IDLE;
		mVelocity = Vector3::Zero;
	}

	// ���̓x�N�g���̐��K��
	inputVec.Normalize();

	mAnimVec = inputVec;

	///// �Ńo�b�N�p //////
	/*if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_DOWN))
	{
		mVelocity.z = -mMoveSpeed;
	}
	else if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_UP))
	{
		mVelocity.z = mMoveSpeed;
	}
	else
	{
		mVelocity.z = 0.0f;
	}*/
}

/*
@fn		�v���C���[���q�b�g�������̏���
@param	_hitObject �q�b�g�����Ώۂ̃Q�[���I�u�W�F�N�g�̃A�h���X
*/
void Player::OnCollision(const GameObject& _hitObject)
{
	//�q�b�g�����I�u�W�F�N�g�̃^�O���擾
	mTag = _hitObject.GetTag();

	// ���Ɛݒu������
	if (mTag == ground)
	{
		mIsGround = true;
	}
}


/*
�A�j���[�V����
*/

// �A�C�h����Ԃ̏���
void Player::mIdleBehavior()
{
	// ���߂Ă��̃X�e�[�g�ɓ���ꍇ
	if (mNowState != mPrevState)
	{
		// �ҋ@�A�j���[�V�����Đ��J�n
		mPrevState = mNowState;
		mSkelComp->PlayAnimation(mAnimations[IDLE], 0.5f);
	}
}

// ������Ԃ̏���
void Player::mRunBehavior()
{
	// ���߂Ă��̃X�e�[�g�ɓ���ꍇ
	if (mNowState != mPrevState)
	{
		mPrevState = mNowState;
		mSkelComp->PlayAnimation(mAnimations[RUN], 1.0f);
	}

	// ��]����
	RotateToNewForward(mAnimVec);
}