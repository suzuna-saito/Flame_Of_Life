#pragma once

/*
@brief 前方宣言
*/
class ItemEffectManager;


// アイテム
class Item :public ItemBase
{
public:
	// コンストラクタ
	Item(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag, const int _num);

	/*
	@fn	デストラクタ
	*/
	~Item() {};

	// 更新
	void UpdateGameObject(float _deltaTime)override;

private:
	// エフェクト
	// アイテムの後ろのエフェクト
	ItemEffectManager* mItemEffectManager;


	// アイテムナンバー
	const int ItemNumber;


	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数
	@param	当たったGameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;

	// アイテムの種類を決定
	void mItemType();

	// ゲッター、セッター
public:
	// アイテムを取得したかどうかをかえす
	bool mGetItemFlag() { return mCollisionFlag; }
};

