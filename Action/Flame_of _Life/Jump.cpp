#include "pch.h"

// �R���X�g���N�^
Jump::Jump(GameObject* _owner)
	: Component(_owner)
	, mVelocity(0.0f)
	, mJumpAccel(600.0f)
	, mJumpSpeed(170.0f)
	, mMaxJumpHeight(3000.0f)
	, mStartFlag(false)
	, mJumpNow(false)
	, mEndFlag(false)
	, mMaxFlag(false)
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
		mVelocity += mJumpAccel;
		mStartFlag = false;
		mEndFlag = false;
		mJumpNow = true;
	}

	if (mVelocity >= mMaxJumpHeight)
	{
		mMaxFlag = true;
	}

	// �W�����v��
	if (mJumpNow)
	{
		if (!mMaxFlag)
		{
			mVelocity += mJumpSpeed;
		}
		else
		{
			mEndFlag = true;
		}

	}
	// �W�����v�I��
	if (mEndFlag)
	{
		mJumpNow = false;
		mMaxFlag = false;
		mVelocity = 0.0f;

		/*mJumpSpeed = 450.0f;*/
	}
}
