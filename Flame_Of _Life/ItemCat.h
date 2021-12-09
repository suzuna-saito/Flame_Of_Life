#pragma once

// 猫のオブジェクト
class ItemCat :public GameObject
{
public:
	// コンストラクタ
	ItemCat(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	/*
	@fn	デストラクタ
	*/
	~ItemCat() {};

	// 更新
	void UpdateGameObject(float _deltaTime)override;

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

