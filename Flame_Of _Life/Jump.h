#pragma once

class Jump
{
public:
	// コンストラクタ
	Jump(Vector3& _pos);
	// デストラクタ
	~Jump();


private:
	// ジャンプの初速度
	float mJumpSpeed;

	// ジャンプの加速度
	float mJumpAccel;
};