#include "pch.h"

BoxCollider::BoxCollider(GameObject* _owner, const GameObject::ObjTag _tag, OnCollisionFunc _func, int _updateOrder, int _collisionOrder)
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

	mWorldBox.m_min = (mObjectBox.m_min * mOwner->GetScale().x);
	mWorldBox.m_max = (mObjectBox.m_max * mOwner->GetScale().x);

	if (mShouldRotate)
	{
		mWorldBox.Rotate(mOwner->GetRotation());
	}

	mWorldBox.m_min += mOwner->GetPosition();
	mWorldBox.m_max += mOwner->GetPosition();
}

