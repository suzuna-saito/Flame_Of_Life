#include "pch.h"

// コンストラクタ
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

// デストラクタ
Jump::~Jump()
{
}

// ジャンプの更新
void Jump::Update(float _deltaTime)
{
	// ジャンプを始めた瞬間
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

	// ジャンプ中
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
	// ジャンプ終了
	if(mAddPos.z <= 0.0f)
	{
 		mJumpNow = false;

		mStartFlag = false;

		mMaxFlag = false;
	}
}
