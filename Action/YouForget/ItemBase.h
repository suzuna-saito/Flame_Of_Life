#pragma once

// アイテムのナンバー
enum class ItemNum : unsigned char
{
	first,

	one = first,
	two,
	three,

	end
};

// アイテムのベースクラス
class ItemBase :public GameObject
{
public:
	// コンストラクタ
	ItemBase(const SceneBase::SceneType _sceneTag, const ObjTag& _objectTag);

	/*
	@fn	デストラクタ
	*/
	~ItemBase() {};

	// ステージにあるアイテムの数
	static int mItemCount;

	// 取得したアイテムを格納するためのデータ構造
	static vector<ItemNum> mGetNumber;

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
	ItemNum mItemNum;

	

// ゲッター、セッター
public:
	// 取得したアイテムを格納
	//void SetItemNames(ItemNum _itemName) { mGetNames.push_back(_itemName); }
};

//// 前置インクリメント
//ItemNum& operator ++(ItemNum& rhs);