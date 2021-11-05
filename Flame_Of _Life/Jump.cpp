#include "pch.h"

// �R���X�g���N�^
Jump::Jump(GameObject* _owner)
	: Component(_owner)
	, mAddPos(Vector3::Zero)
	, mJumpAccel(5.0f)
	, mJumpSpeed(2.0f)
	, mMaxJumpHeight(50.0f)
	, mJumpNow(false)
	, mStartFlag(false)
{
}

// �f�X�g���N�^
Jump::~Jump()
{
}

// �W�����v�̍X�V
void Jump::Update(float _deltaTime)
{
	// �W�����v���n�߂��u��
	if (!mStartFlag)
	{
		mAddPos = Vector3::Zero;
		mAddPos.z += mJumpAccel;

		mStartFlag = true;
	}

	// �W�����v��
	if (mJumpNow && mAddPos.z <= mMaxJumpHeight)
	{
		mAddPos.z += mJumpSpeed;
	}
	// �W�����v�I��
	else
	{
 		mJumpNow = false;

		mStartFlag = false;
	}
}
