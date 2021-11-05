#include "pch.h"

// コンストラクタ
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

	// ジャンプ中
	if (mJumpNow && mAddPos.z <= mMaxJumpHeight)
	{
		mAddPos.z += mJumpSpeed;
	}
	// ジャンプ終了
	else
	{
 		mJumpNow = false;

		mStartFlag = false;
	}
}
