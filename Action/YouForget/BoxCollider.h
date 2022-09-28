/*
@file	BoxCollider.h
@brief	ボックスの当たり判定を行うコンポーネント
*/

/*
@brief	プリプロセッサ
*/
#pragma once

class BoxCollider final : public ColliderComponent
{
public:

	/*
	@fn		コンストラクタ
	@param	_owner アタッチするゲームオブジェクトのポインタ
	@param	_tag アタッチするゲームオブジェクトの当たり判定のタグ
	@param	_func 他のオブジェクトと当たった時に呼ばれる関数ポインタ(GetOnCollisionFuncを呼ぶ)
	@param	_updateOrder コンポーネントの更新順番（数値が小さいほど早く更新される
	@param	_collisionOrder 当たり判定時に、めり込みから動かす処理の優先度を決める数値
	*/
	BoxCollider(class GameObject* _owner, ColliderTag _tag, OnCollisionFunc _func, int _updateOrder = 200, int _collisionOrder = 100);

	/*
	@fn	デストラクタ
	*/
	virtual ~BoxCollider();

	/*
	@fn	Transformのワールド変換
	*/
	void OnUpdateWorldTransform() override;

	/*
	@fn	ヒットしたオブジェクトが二つ以上あった場合、どのオブジェクトと押し戻しをするか
			タグで調べた後にまたTransformのワールド変換をする
	@brief ヒットしたオブジェクト二つの間にいた場合、引っかかったり、すり抜けするので
			それを防ぐためにもう一度Transformのワールド変換をする
	*/
	void Refresh() override;

private:

	//オブジェクトに設定する用のボックス（中心をオブジェクトの中心にする）
	AABB mObjectBox;
	//当たり判定するときに使うボックス（中心をワールド座標の中心にする）
	AABB mWorldBox;
	//回転させるか
	bool mShouldRotate;

public: //ゲッターセッター

	/*
	@fn		当たり判定時に使うワールド空間でのAABBを取得する
	@return 中心をワールド座標に合わせたAABBの構造体(AABB型)
	*/
	AABB GetWorldBox() const { return mWorldBox; }

	/*
	@fn		当たり判定に使うAABBの設定
	@param	_box オブジェクトの大きさに合わせたAABBの構造体
	*/
	void SetObjectBox(const AABB& _box) { mObjectBox = _box; }
};