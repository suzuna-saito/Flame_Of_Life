#pragma once

class Jump
{
public:
	// コンストラクタ
	Jump();
	// デストラクタ
	~Jump();

	void Update();

private:
	// ジャンプの初速度
	float mJumpSpeed;

	// ジャンプの加速度
	float mJumpAccel;
};