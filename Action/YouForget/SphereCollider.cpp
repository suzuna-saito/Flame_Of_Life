/*
@file	SphereCollider.h
@brief	球の当たり判定を行うコンポーネント
*/

/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_owner アタッチするゲームオブジェクトのポインタ
@param	_tag アタッチするゲームオブジェクトの当たり判定のタグ
@param	_func 他のオブジェクトと当たった時に呼ばれる関数ポインタ(GetOnCollisionFuncを呼ぶ)
@param	_updateOrder コンポーネントの更新順番（数値が小さいほど早く更新される）
@param	_collisionOrder 当たり判定時に、めり込みから動かす処理の優先度を決める数値
*/
SphereCollider::SphereCollider(GameObject* _owner, GameObject::ObjTag _tag, OnCollisionFunc _func, int _updateOrder, int _collisionOrder)
	: ColliderComponent(_owner, _tag, _updateOrder, _collisionOrder)
	, mObjectSphere(Vector3::Zero, 0.0f)
	, mWorldSphere(Vector3::Zero, 0.0f)
{
	PHYSICS->AddSphere(this, _func);
}

/*
@fn	デストラクタ
*/
SphereCollider::~SphereCollider()
{
	PHYSICS->RemoveSphere(this);
}

/*
@fn	Transformのワールド変換
*/
void SphereCollider::OnUpdateWorldTransform()
{
	Refresh();
	PHYSICS->HitCheck(this);
}

/*
@fn		ヒットしたオブジェクトが二つ以上あった場合、どのオブジェクトと押し戻しをするか
		タグで調べた後にまたTransformのワールド変換をする
@detail ヒットしたオブジェクト二つの間にいた場合、引っかかったり、すり抜けするので
		それを防ぐためにもう一度Transformのワールド変換をする
*/
void SphereCollider::Refresh()
{
	//ワールド座標での中心位置を更新する
	mWorldSphere.m_center = mObjectSphere.m_center + mOwner->GetPosition();
	//ワールド空間での球の大きさを更新する
	mWorldSphere.m_radius = mObjectSphere.m_radius * mOwner->GetScale().x;
}