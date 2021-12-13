#pragma once


// 人型アイテムのオブジェクト
class ItemChara :public ItemBase
{
public:
	// コンストラクタ
	ItemChara(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	/*
	@fn	デストラクタ
	*/
	~ItemChara() {};

	// 更新
	void UpdateGameObject(float _deltaTime)override;

private:

	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数
	@param	当たったGameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;

};

