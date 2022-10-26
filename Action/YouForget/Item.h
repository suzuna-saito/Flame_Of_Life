#pragma once

/*
@brief 前方宣言
*/
class ItemEffectManager;


// アイテム
class Item :public ItemBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_pos">ポジション</param>
	/// <param name="_size">サイズ</param>
	/// <param name="_objectTag">自身のタグ</param>
	/// <param name="_sceneTag">現在のシーン</param>
	/// <param name="_num">何個目のアイテムか</param>
	Item(const Vector3& _pos, const Vector3& _size, const CollisionTag& _objectTag, const SceneBase::SceneType _sceneTag, const int _num);

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

	// アイテムがまだ存在しているかのフラグ true _存在する false _存在しない
	bool mItemExistsFlag;

	// アイテムの透明度をさげるかどうか true _下げる false _下げない
	bool mAlphaDownFlag;
	// アイテムが点滅し始める時間
	int mItemFlashingTime;
	// アイテムのそれぞれの生存時間
	int mItemExistsTime;

	int MItemExistsOneTime;
	int MItemExistsTwoTime;
	int MItemExistsThreeTime;

	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数
	@param	当たったGameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;

	// アイテムの種類を決定
	void mItemType(int _num);

	// アイテムの生存時間の処理
	void mItemExists();

	// ゲッター、セッター
public:
	// アイテムが存在してるかどうかをかえす
	bool mGetItemExistsFlag() { return mItemExistsFlag; }
};

