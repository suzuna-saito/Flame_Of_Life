#include "pch.h"

// �R���X�g���N�^
Jump::Jump(GameObject* _owner)
	: Component(_owner)
	, mVelocity(0.0f)
	, MJumpAccel(150.0f)
	, MJumpSpeed(30.0f)
	, mStartFlag(false)
	, mJumpNow(false)
	, mEndFlag(false)
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
	if (mStartFlag)
	{
		mVelocity += MJumpAccel;
		mStartFlag = false;
		mEndFlag = false;
		mJumpNow = true;
	}

	// �W�����v��
	if (!mEndFlag && mJumpNow)
	{
		mVelocity += MJumpSpeed;
	}
	// �W�����v�I��
	if(mEndFlag)
	{
		mJumpNow = false;
		mVelocity = 0.0f;
	}
}
