#pragma once

// アイテム
class ItemTest :public ItemBase
{
public:
	// コンストラクタ
	ItemTest(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag, const int _num);

	/*
	@fn	デストラクタ
	*/
	~ItemTest() {};

	// 更新
	void UpdateGameObject(float _deltaTime)override;

private:
	// アイテムナンバー
	const int ItemNumber;

	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数
	@param	当たったGameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;

	// アイテムの種類を決定
	void mItemType();

};

