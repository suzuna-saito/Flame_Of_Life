/*
@brief	�C���N���[�h
*/
#include "pch.h"

// �ÓI�����o
// �v���C���[������\���ǂ����@true _�\ false _�s�\
bool Player::mOperable = true;

/*
@fn		�R���X�g���N�^
@param	_pos �v���C���[�̍��W
@param	_size �v���C���[�̃T�C�Y
@param	_objectTag �v���C���[�̃^�O
@param	_sceneTag �V�[���̃^�O
*/
Player::Player(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, _objectTag)
	, mCameraPos(Vector3(0, -1300, 1320))
	, mReturnPos(_pos)
	, mDifference(Vector3::Zero)
	, MStartCameraPos(2000.0f)
	, MAddCameraPos(100.0f)
	, MCameraPointZ(66.0f)
	, MChagePosZ(70.0f)
	, MRedoingPosZ(-700.0f)
	, MReturnAddZ(100.0f)
	, MRedoingSpeedZ(900.0f)
	, MMaxJumpVel(1700.0f)
	, mStartFlag(true)
	, mVibrationFlag(false)
	, mNowState(playerState::idle)
	, mPrevState(playerState::idle)
{
	//GameObject�����o�ϐ��̏�����
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	//��������Player�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mSkelComp = new SkeletalMeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mSkelComp->SetMesh(RENDERER->GetMesh("Assets/Player/doll.gpmesh"));

	// �X�P���g���̓ǂݍ���
	mSkelComp->SetSkeleton(RENDERER->GetSkeleton("Assets/Player/doll.gpskel"));

	// �A�j���[�V�����̓ǂݍ���
	mAnimations.resize((int)playerState::stateNum); // �z����m�ہimAnimations��vector�j(STSTE_NUM��enum�̒��̐�)
	mAnimations[(int)playerState::idle] = RENDERER->GetAnimation("Assets/Player/idle.gpanim");
	mAnimations[(int)playerState::run] = RENDERER->GetAnimation("Assets/Player/run.gpanim");

	//�A�j���[�V�����̍Đ�
	mSkelComp->PlayAnimation(mAnimations[(int)playerState::idle]);

	// �G�t�F�N�g
	// �v���C���[�����������̃G�t�F�N�g
	mFallEffectManager = new FallEffectManager(_objectTag, _sceneTag, this);

	//�v���C���[���g�̓����蔻��(�{�b�N�X)
	mSelfBoxCollider = new BoxCollider(this, ColliderTag::playerTag, GetOnCollisionFunc());
	AABB box = { Vector3(750.0f,-750.0f,0.0f),Vector3(-750.0f,750.0f,3500.0f) };
	mSelfBoxCollider->SetObjectBox(box);


	//��]����                        ����]����l
	float radian = Math::ToRadians(90.0f);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::UnitZ, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);

	// ���������蔻��̐���
	mLegs = new LegsCollider(this, Tag::playerLegs, _sceneTag);

	// �W�����v��ǉ�
	mJump = new Jump(this);


	// �Ńo�b�N�p //
	mDebug = false;

}

/*
@fn		�v���C���[�̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void Player::UpdateGameObject(float _deltaTime)
{
	//// �J���������̍����܂Ŏ����Ă���
	//if (mCameraPos.z <= MStartCameraPos && !mStartFlag)
	//{
	//	mCameraPos.z += MAddCameraPos* _deltaTime;
	//}
	//else if (mCameraPos.z >= MStartCameraPos)
	//{
	//	// ���̍����܂ŗ�����s���ł���悤�ɂ���
	//	mOperable = true;
	//	mStartFlag = true;
	//}

	if (mPosition.z >= MChagePosZ)
	{
		//�v���C���[�������낷�ʒu�ɃJ�������Z�b�g
		mMainCamera->SetViewMatrixLerpObject(mCameraPos, Vector3(mPosition.x, mPosition.y + 50.0f, MCameraPointZ));
	}
	else
	{
		//�v���C���[�������낷�ʒu�ɃJ�������Z�b�g
		mMainCamera->SetViewMatrixLerpObject(mCameraPos, mPosition);
	}
	//�v���C���[�������猩��ʒu�ɃJ�������Z�b�g
	//mMainCamera->SetViewMatrixLerpObject(Vector3(1000, 0, 200), mPosition);
	// �f�o�b�N�p
	//mMainCamera->SetViewMatrixLerpObject(Vector3(0, -1000, 200), mPosition + testPos);


	// ���݂̏�Ԃ��炻�ꂼ��̂ӂ�܂����s���֐��ɃW�����v
	switch (mNowState)
	{
	case playerState::idle:
		mIdleBehavior();
		break;

	case playerState::run:
		mRunBehavior();
		break;

	default:
		break;
	}

	// �W�����v���Ă���W�����v�͂𑫂�
	if (mJump->GetJumpFlag())
	{
		mVelocity.z += mJump->GetVelocity();
		mLegs->SetIsGround(false);
	}

	// velocity����萔�܂ōs������A�W�����v�͂��Ȃ���
	if (mVelocity.z >= MMaxJumpVel)
	{
		mJump->SetEndJump(true);
	}

	// �d��
	if (!mLegs->GetIsGround() && !mDebug && mOperable)
	{
		mVelocity.z -= MGravity;
	}
	else if(mOperable)
	{
		mVelocity.z = 0.0f;
	}
	

	// ���W���Z�b�g
	mPosition += (mVelocity + mInputSpeed) * _deltaTime;

	// ��Ԃ��؂�ւ������A�j���[�V�������J�n
	if (mNowState != mPrevState)
	{
		mSkelComp->PlayAnimation(mAnimations[(int)mNowState], 0.5f);
	}

	if (!mLegs->GetIsGround())
	{
		ComputeWorldTransform();
	}

	//���̃t���[���̃X�e�[�g��1�O�̃X�e�[�g�ɂȂ�
	mPrevState = mNowState;

	
	// �v���C���[����������
	if (mPosition.z <= MRedoingPosZ && mOperable)
	{
		// �U���t���O��true�ɂ���
		mVibrationFlag = true;
		// ���삪�o���Ȃ�����
		mOperable = false;

		mVelocity = Vector3::Zero;
	}

	if (!mOperable)
	{
		// ���A�ʒu�܂ňړ�������
		mRedoing(mPosition, mReturnPos);
	}


	// �|�W�V�������Z�b�g
	SetPosition(mPosition);
	mLegs->SetIsGround(false);
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
	mInputSpeed = Vector3::Zero;

	if (mOperable)
	{
		// W�ŉ��Ɉړ�
		if (_keyState.m_controller.GetLAxisVec().y < 0.0f ||
			_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W))
		{
			inputVec.y = 1.0f;
		}
		// S�Ŏ�O�Ɉړ�
		else if (_keyState.m_controller.GetLAxisVec().y > 0.0f ||
			_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S))
		{
			inputVec.y = -1.0f;
		}

		// A�ō��Ɉړ�
		if (_keyState.m_controller.GetLAxisVec().x < 0.0f ||
			_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A))
		{
			inputVec.x = 1.0f;
		}
		// D�ŉE�Ɉړ�
		else if (_keyState.m_controller.GetLAxisVec().x > 0.0f ||
			_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D))
		{
			inputVec.x = -1.0f;
		}

		// A�{�^�����X�y�[�X�ŃW�����v
		if ((_keyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == ButtonState::Pressed ||
			_keyState.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::Pressed) &&
			mLegs->GetIsGround())
		{
			mJump->SetJumpStart(true);
		}

		// �����ꂩ��������Ă�����
		if (inputVec != Vector3::Zero)
		{
 			mNowState = playerState::run;

			// ���̓x�N�g���̐��K��
			inputVec.Normalize();
			// �ړ�
			mInputSpeed = inputVec * mMoveSpeed;
		}
		else
		{ 
			mNowState = playerState::idle;
		}

		
		// �A�j���[�V�����������
		mAnimVec = inputVec;
	}
	/*else if (mVibrationFlag)
	{
		SDL_GameControllerRumble(_keyState.m_controller)
	}*/
}

/*
@fn		��`�Ƌ�`�̉����߂�
@param	_myAABB	��ɂ���I�u�W�F�N�g�̋�`�����蔻��
@param	_pairAABB �q�b�g����I�u�W�F�N�g�̋�`�����蔻��
@param	_pairTag �q�b�g����I�u�W�F�N�g�̃^�O
*/
void Player::FixCollision(const AABB& _myAABB, const AABB& _pairAABB, const Tag& _pairTag)
{
	Vector3 ment = Vector3::Zero;
	CalcCollisionFixVec(_myAABB, _pairAABB, ment);

	SetPosition(mPosition + ment);
}

/*
@fn		�v���C���[���q�b�g�������̏���
@param	_hitObject �q�b�g�����Ώۂ̃Q�[���I�u�W�F�N�g�̃A�h���X
*/
void Player::OnCollision(const GameObject& _hitObject)
{
	//�q�b�g�����I�u�W�F�N�g�̃^�O���擾
	Tag hitObjectTag = _hitObject.GetTag();

	if (mOperable &&
		(hitObjectTag == Tag::ground ||
		hitObjectTag == Tag::Switch))
	{
		// �����߂�
		FixCollision(mSelfBoxCollider->GetWorldBox(), _hitObject.GetAabb(), mTag);
	}
}


// ���A�ʒu�܂ňړ�������
void Player::mRedoing(Vector3 _nowPos, const Vector3 _returnPos)
{
	Vector3 returnPos = Vector3::Zero;

	returnPos = _returnPos;
	returnPos.z += MReturnAddZ;
	// ���シ��Ƃ�
	if (mPosition.z < returnPos.z)
	{
		mVelocity.z = MRedoingSpeedZ;
	}
	// ���サ����
	else
	{
		mVelocity.z = 0.0f;

		// ���݂̃|�W�V�����ƃ��X�|�[���n�_�̍��W��p���Đ��`��Ԃ��s���A���̍��W���v�Z����
		mDifference = Vector3::Lerp(_nowPos, returnPos, 0.05f);

		mPosition = mDifference;
	}
	
	Vector3 distance = Vector3::Zero;

	// �����x�N�g��
	distance = returnPos - mPosition;

	// 1�ɋ߂�������
	if (Math::NearZero(distance.Length(),5.0f))
	{
		// �s�����\�ɂ���
		mOperable = true;
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
		mSkelComp->PlayAnimation(mAnimations[(int)playerState::idle], 0.5f);
	}
}

// ������Ԃ̏���
void Player::mRunBehavior()
{
	// ���߂Ă��̃X�e�[�g�ɓ���ꍇ
	if (mNowState != mPrevState)
	{
		mPrevState = mNowState;
		mSkelComp->PlayAnimation(mAnimations[(int)playerState::run], 1.0f);
	}

	// ��]����
	RotateToNewForward(mAnimVec);
}