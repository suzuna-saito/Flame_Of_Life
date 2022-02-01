/*
@file	BoxCollider.h
@brief	ボックスの当たり判定を行うコンポーネント
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
BoxCollider::BoxCollider(GameObject* _owner, ColliderTag _tag, OnCollisionFunc _func, int _updateOrder, int _collisionOrder)
	: ColliderComponent(_owner, _tag, _updateOrder, _collisionOrder)
	, mObjectBox(Vector3::Zero, Vector3::Zero)
	, mWorldBox(Vector3::Zero, Vector3::Zero)
	, mShouldRotate(true)
{
	PHYSICS->AddBox(this, _func);
}

/*
@fn		デストラクタ
*/
BoxCollider::~BoxCollider()
{
	PHYSICS->RemoveBox(this);
}

/*
@fn		Transformのワールド変換
*/
void BoxCollider::OnUpdateWorldTransform()
{
	Refresh();
	PHYSICS->HitCheck(this);
}

/*
@fn		ヒットしたオブジェクトが二つ以上あった場合、どのオブジェクトと押し戻しをするか
		タグで調べた後にまたTransformのワールド変換をする
@brief	ヒットしたオブジェクト二つの間にいた場合、引っかかったり、すり抜けするので
		それを防ぐためにもう一度Transformのワールド変換をする
*/
void BoxCollider::Refresh()
{
	mWorldBox = mObjectBox;

	mWorldBox.m_min = (mObjectBox.m_min * mOwner->GetScale());
	mWorldBox.m_max = (mObjectBox.m_max * mOwner->GetScale());

	if (mShouldRotate)
	{
		mWorldBox.Rotate(mOwner->GetRotation());
	}

	mWorldBox.m_min += mOwner->GetPosition();
	mWorldBox.m_max += mOwner->GetPosition();
}

