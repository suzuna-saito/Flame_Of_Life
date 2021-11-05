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
	float mJumpSpeed;
	// ジャンプの加速度
	float mJumpAccel;
	// 最高ジャンプ地点
	float mMaxJumpHeight;

	// ジャンプが開始した瞬間かどうか
	bool mStartFlag;
	// ジャンプ中かどうか
	bool mJumpNow;

	// ポジション
	Vector3 mAddPos;

public:
	// ジャンプしてるかどうかセットする
	void SetJumpFlag(bool _flag) { mJumpNow = _flag; }
	// ジャンプしてるかどうかを返す
	bool GetJumpFlag() { return mJumpNow; }

	// 
	Vector3 GetAddPos() { return mAddPos; }
};