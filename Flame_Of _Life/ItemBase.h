#pragma once

// アイテムのベースクラス
class ItemBase :public GameObject
{
public:
	// コンストラクタ
	ItemBase(const SceneBase::Scene _sceneTag, const Tag& _objectTag);

	/*
	@fn	デストラクタ
	*/
	~ItemBase() {};

	static int mItemCount;

protected:
	//ゲームオブジェクトのメッシュポインタ変数
	MeshComponent* mMeshComponent;

	// 四角の当たり判定を生成
	BoxCollider* mSelfBoxCollider;

	// プレイヤーと当たったかどうかの判定
	bool mCollisionFlag;
private:
};

