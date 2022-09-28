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
	/// <param name="_size">サイズ</param>
	/// <param name="_objectTag">自身のタグ</param>
	/// <param name="_sceneTag">現在のシーンタグ</param>
	GoalObj(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);
	// デストラクタ
	~GoalObj() {};

	/// <summary>
	/// ゴールオブジェクトの更新処理
	/// </summary>
	/// <param name="_deltaTime">最後のフレームを完了するのに要した時間</param>
	void UpdateGameObject(float _deltaTime)override;

	static bool mGoalFlag;          // ゴールしたかどうか

private:
	MeshComponent* mMeshComponent;  //ゲームオブジェクトのメッシュポインタ変数
	BoxCollider* mSelfBoxCollider;  // 当たり判定(四角)

	class GoalEffectManager* mGoalEffectManager;

	/// <summary>
	/// 当たり判定が行われHitした際に呼ばれる関数
	/// </summary>
	/// <param name="_hitObject">Hitした対象のゲームオブジェクトのアドレス</param>
	void OnCollision(const GameObject& _hitObject)override;

public: // セッター、ゲッター
};

