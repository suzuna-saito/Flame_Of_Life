#pragma once


// 花のオブジェクト
class Rose :public GameObject
{
public:
	// コンストラクタ
	Rose(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	/*
	@fn	デストラクタ
	*/
	~Rose() {};

	// 更新
	void UpdateGameObject(float _deltaTime)override;

	// アイテムが生成された回数
	static int mItemCount;
private:

	//ゲームオブジェクトのメッシュポインタ変数
	MeshComponent* mMeshComponent;

	// 四角の地面の当たり判定を生成
	BoxCollider* mSelfBoxCollider;

	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数
	@param	当たったGameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;

	// プレイヤーと当たったかどうかの判定
	bool mCollisionFlag;
};

