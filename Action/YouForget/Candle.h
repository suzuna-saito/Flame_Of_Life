#pragma once

/*
* ゴールオブジェクトの処理
*/
class Candle :public GameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_pos">ポジション</param>
	/// <param name="_size">サイズ</param>
	/// <param name="_objectTag">自身のタグ</param>
	/// <param name="_sceneTag">現在のシーンタグ</param>
	Candle(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::SceneType _sceneTag);
	// デストラクタ
	~Candle() {};

	/// <summary>
	/// ゴールオブジェクトの更新処理
	/// </summary>
	/// <param name="_deltaTime">最後のフレームを完了するのに要した時間</param>
	void UpdateGameObject(float _deltaTime)override;

	static bool mGoalFlag;          // ゴールしたかどうか

private:
	MeshComponent* mMeshComponent;  //ゲームオブジェクトのメッシュポインタ変数
	BoxCollider* mSelfBoxCollider;  // 当たり判定(四角)

	/// <summary>
	/// 当たり判定が行われHitした際に呼ばれる関数
	/// </summary>
	/// <param name="_hitObject">Hitした対象のゲームオブジェクトのアドレス</param>
	void OnCollision(const GameObject& _hitObject)override;

	bool mDrawFireFlag;    // ろうそくの火を描画しているかどうか

public: // セッター、ゲッター
};

