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

	// 取得したアイテムを格納するためのデータ構造
	static vector<itemNames> mGetNames;

protected:
	//ゲームオブジェクトのメッシュポインタ変数
	MeshComponent* mMeshComponent;

	// 四角の当たり判定を生成
	BoxCollider* mSelfBoxCollider;

	// アイテムの動き
	float mMove;
	float mMaxMove;
	float mMinMove;
	bool mUpFlag;

	// プレイヤーと当たったかどうかの判定
	bool mCollisionFlag;

	// アイテムの種類
	itemNames mItemName;

	

// ゲッター、セッター
public:
	// 取得したアイテムを格納 @@@ いらなくね
	void SetItemNames(itemNames _itemName) { mGetNames.push_back(_itemName); }
	// 取得したアイテムを返す
	//static const vector<itemNames> GetItemNames() { return mGetNames; }
};

//// 前置インクリメント
//itemNames& operator ++(itemNames& rhs);