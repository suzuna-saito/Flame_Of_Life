#pragma once

/*
* ゴールオブジェクトの処理
*/
class GoalObj :public GameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_pos">ポジション</param>
	GoalObj(const Vector3 _pos);
	// デストラクタ
	~GoalObj() {};

	static bool mGoalFlag;	// ゴールしたかどうか true:した

private:
	/// <summary>
	/// 当たり判定が行われHitした際に呼ばれる関数
	/// </summary>
	/// <param name="_hitObject">Hitした対象のゲームオブジェクトのアドレス</param>
	void OnCollision(const GameObject& _hitObject)override;

	class BoxCollider* mSelfBoxCollider;	// 当たり判定(四角)
};