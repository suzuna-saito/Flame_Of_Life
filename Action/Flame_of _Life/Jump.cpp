#include "pch.h"

// コンストラクタ
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

// デストラクタ
Jump::~Jump()
{
}

// ジャンプの更新
void Jump::Update(float _deltaTime)
{
	// ジャンプを始めた瞬間
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

	// ジャンプ中
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
	// ジャンプ終了
	if (mEndFlag)
	{
		mJumpNow = false;
		mMaxFlag = false;
		mVelocity = 0.0f;

		/*mJumpSpeed = 450.0f;*/
	}
}
