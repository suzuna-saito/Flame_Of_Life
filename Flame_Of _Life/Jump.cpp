#include "pch.h"

// �R���X�g���N�^
Jump::Jump(GameObject* _owner)
	: Component(_owner)
	, mAddPos(Vector3::Zero)
	, mJumpAccel(7.0f)
	, mJumpSpeed(4.0f)
	, mMaxJumpHeight(35.0f)
	, mJumpNow(false)
	, mStartFlag(false)
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
	if (!mStartFlag)
	{
		mAddPos = Vector3::Zero;
		mAddPos.z += mJumpAccel;

		mStartFlag = true;
	}

	if (mAddPos.z >= mMaxJumpHeight)
	{
		mMaxFlag = true;
	}

	// �W�����v��
	if (mJumpNow)
	{
		if (!mMaxFlag)
		{
			mAddPos.z += mJumpSpeed;
		}
		else
		{
			mAddPos.z -= mJumpSpeed;
		}
		
	}
	// �W�����v�I��
	if(mAddPos.z <= 0.0f)
	{
 		mJumpNow = false;

		mStartFlag = false;

		mMaxFlag = false;
	}
}
