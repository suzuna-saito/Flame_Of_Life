#pragma once

class Jump:public Component
{
public:
	// コンストラクタ
	Jump(GameObject* _owner);
	// デストラクタ
	~Jump();

	// 更新処理
	void Update(float _deltaTime)override;

private:
	// ジャンプの初速度
	float MJumpSpeed;
	// ジャンプの加速度
	float MJumpAccel;
	
	// ジャンプが開始した瞬間かどうか
	bool mStartFlag;
	// ジャンプ中かどうか
	bool mJumpNow;
	// ジャンプを終了するかどうか
	bool mEndFlag;

	// ポジション
	float mVelocity;
public:
	// ジャンプしてるかどうかセットする
	void SetJumpStart(bool _flag) { mStartFlag = _flag; }

	// ジャンプ終了するかどうかセットする
	void SetEndJump(bool _flag) { mEndFlag = _flag; }

	// ジャンプしてるかどうかを返す
	const bool GetJumpStartFlag() const { return mStartFlag; }
	const bool GetJumpFlag() const { return mJumpNow; }

	// ジャンプで増えたZ軸の増加分
	const float GetVelocity() const { return mVelocity; }
};