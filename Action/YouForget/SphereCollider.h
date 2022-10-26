/*
@file	SphereCollider.h
@brief	球の当たり判定を行うコンポーネント
*/

/*
@brief	プリプロセッサ
*/
#pragma once


class SphereCollider final : public ColliderComponent
{
public:

	/*
	@fn		コンストラクタ
	@param	_owner アタッチするゲームオブジェクトのポインタ
	@param	_tag アタッチするゲームオブジェクトの当たり判定のタグ
	@param	_func 他のオブジェクトと当たった時に呼ばれる関数ポインタ(GetOnCollisionFuncを呼ぶ)
	@param	_updateOrder コンポーネントの更新順番（数値が小さいほど早く更新される）
	@param	_collisionOrder 当たり判定時に、めり込みから動かす処理の優先度を決める数値
	*/
	SphereCollider(GameObject* _owner, GameObject::ObjTag _tag, OnCollisionFunc _func, int _updateOrder = 200, int _collisionOrder = 100);

	/*
	@fn	デストラクタ
	*/
	virtual ~SphereCollider();

	/*
	@fn	Transformのワールド変換
	*/
	void OnUpdateWorldTransform() override;

	/*
	@fn		ヒットしたオブジェクトが二つ以上あった場合、どのオブジェクトと押し戻しをするか
			タグで調べた後にまたTransformのワールド変換をする
	@detail ヒットしたオブジェクト二つの間にいた場合、引っかかったり、すり抜けするので
			それを防ぐためにもう一度Transformのワールド変換をする
	*/
	void Refresh() override;

private:

	//オブジェクトに設定する用の球（中心をオブジェクトの中心にする）
	Sphere mObjectSphere;
	//当たり判定するときに使う球（中心をワールド座標の中心にする）
	Sphere mWorldSphere;

public: //ゲッターセッター

	/*
	@fn		当たり判定時に使うワールド空間でのSphereを取得する
	@return 中心をワールド座標に合わせたSphereの構造体(Sphere型)
	*/
	Sphere GetWorldSphere() const { return mWorldSphere; }

	/*
	@fn		当たり判定に使うSphereの設定
	@param	_sphere オブジェクトの大きさに合わせたSphereの構造体
	*/
	void SetObjectSphere(const Sphere& _sphere) { mObjectSphere = _sphere; }
};

