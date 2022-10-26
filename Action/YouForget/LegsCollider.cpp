#include "pch.h"

// コンストラクタ
LegsCollider::LegsCollider(Player* _owner, const ObjTag& _objectTag, const SceneBase::SceneType _sceneTag)
	:GameObject(ObjTag::ePlayerLegs)
	, mIsGround(false)
	, mOwner(_owner)
{
	//プレイヤー足元の当たり判定(ボックス)
	mLegsBoxCollider = new BoxCollider(this, GameObject::ObjTag::ePlayerLegs, GetOnCollisionFunc());
	AABB Legsbox = { Vector3(-20.0f,-20.0f,-10.0f),Vector3(20.0f,20.0f,5.0f) };
	mLegsBoxCollider->SetObjectBox(Legsbox);
}

void LegsCollider::UpdateGameObject(float _deltaTime)
{
	SetPosition(mOwner->GetPosition());
	mAabb = mLegsBoxCollider->GetWorldBox();
	//mIsGround = false;
}

// 当たり判定
void LegsCollider::OnCollision(const GameObject& _hitObject)
{
	//ヒットしたオブジェクトのタグを取得
	ObjTag hitObjectTag = _hitObject.GetTag();
	
	if (hitObjectTag == ObjTag::eGround)
	{
		// 接地フラグをtrueにする
		mIsGround = true;
	}

	if (hitObjectTag == ObjTag::eSwitchCenter && Player::mOperable)
	{
		mOwner->SetReturnPos(_hitObject.GetPosition());
	}
}
