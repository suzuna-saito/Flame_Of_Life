#pragma once

// アイテムの名前
enum class itemNames : unsigned char
{
	first,

	cat = first,      // 猫
	chair,    // いす
	chara,    // ミニキャラ
	lighter,  // ライト
	sword,    // 剣
	tree,      // 木

	end
};

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

	// ステージにあるアイテムの数
	static int mItemCount;

protected:
	//ゲームオブジェクトのメッシュポインタ変数
	MeshComponent* mMeshComponent;

	// 四角の当たり判定を生成
	BoxCollider* mSelfBoxCollider;

	// プレイヤーと当たったかどうかの判定
	bool mCollisionFlag;
private:
	// 取得したアイテムを格納するためのデータ構造
	vector<itemNames> mNames;

// ゲッター、セッター
public:
	// 取得したアイテムを格納
	void SetItemNames(itemNames _itemName) { mNames.push_back(_itemName); }

	const vector<itemNames> GetItemNames() const { return mNames; }
};

//// 前置インクリメント
//itemNames& operator ++(itemNames& rhs);