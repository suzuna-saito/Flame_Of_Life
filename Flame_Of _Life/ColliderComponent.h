/*
@file	ColliderComponent.h
@brief	当たり判定を行うコンポーネントの規定クラス
*/

/*
@brief	プリプロセッサ
*/
#pragma once


/*
@enum　GameObjectタグ
衝突相手を判別するために使用
*/
enum class ColliderTag : unsigned char
{
	start,

	OtherTag = start,
	CameraTag,
	playerTag,
	playerLegsTag,
	groundTag,
	itemTag,

	end,
};

// 前置インクリメント
ColliderTag& operator ++(ColliderTag& rhs);


class ColliderComponent : public Component
{
public:
		/*
		@fn		コンストラクタ
		@param	_owner アタッチするゲームオブジェクトのポインタ
		@param	_tag アタッチするゲームオブジェクトの当たり判定のタグ
		@param	_updateOrder コンポーネントの更新順番（数値が小さいほど早く更新される）
		@param  _collisionOrder 当たり判定時に、めり込みから動かす処理の優先度を決める数値
		*/
	ColliderComponent(GameObject* _owner, ColliderTag _tag, int _updateOrder = 200, int _collisionOrder = 100);
protected:

	//アタッチするゲームオブジェクトの当たり判定のタグ
	ColliderTag mTag;

private:

		//実体を伴う当たり判定をするかどうか
	bool mTriggerFlag;
	//数値が大きい方を優先してめり込みから動かす処理をする（0以下は動かさない）
	int	 mCollisionOrder;
public: //ゲッターセッター
	/*
	@fn		めり込み動かす際の優先度を示す数値を取得する
	@return 優先度を示す数値(int型)
	*/
	int GetCollisionOrder() const { return mCollisionOrder; }

	/*
	@fn		アタッチするゲームオブジェクトの当たり判定のタグを取得する
	@return	タグの番号(enum型 ColliderTag)
	*/
	ColliderTag GetTag() const { return mTag; };
};

