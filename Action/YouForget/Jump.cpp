#include "pch.h"

// コンストラクタ
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
		mVelocity += MJumpAccel;
		mStartFlag = false;
		mEndFlag = false;
		mJumpNow = true;
	}

	// ジャンプ中
	if (!mEndFlag && mJumpNow)
	{
		mVelocity += MJumpSpeed;
	}
	// ジャンプ終了
	if(mEndFlag)
	{
		mJumpNow = false;
		mVelocity = 0.0f;
	}
}
