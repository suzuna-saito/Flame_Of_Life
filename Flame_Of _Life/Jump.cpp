#include "pch.h"

// コンストラクタ
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
			mAddPos.z -= mJumpSpeed+2.0f;
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
