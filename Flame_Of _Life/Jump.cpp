#include "pch.h"

// �R���X�g���N�^
Jump::Jump(GameObject* _owner)
	: Component(_owner)
	, mAddPos(Vector3::Zero)
	, mJumpAccel(2.0f)
	, mJumpSpeed(5.0f)
	, mMaxJumpHeight(50.0f)
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
			mAddPos.z -= mJumpSpeed+2.0f;
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
