#include "pch.h"

// コンストラクタ
LegsCollider::LegsCollider(Player* _owner, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	:GameObject(_sceneTag, _objectTag)
	, mIsGround(false)
	, mOwner(_owner)
{
	//プレイヤー足元の当たり判定(ボックス)
	mLegsBoxCollider = new BoxCollider(this, ColliderTag::playerLegsTag, GetOnCollisionFunc());
	AABB Legsbox = { Vector3(-30.0f,-30.0f,-10.0f),Vector3(30.0f,30.0f,5.0f) };
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
	Tag hitObjectTag = _hitObject.GetTag();
	
	if (hitObjectTag == Tag::ground ||
		hitObjectTag == Tag::Switch)
	{
		// 接地フラグをtrueにする
		mIsGround = true;
	}

	if (hitObjectTag == Tag::SwitchCenter && Player::mOperable)
	{
		mOwner->SetReturnPos(_hitObject.GetPosition());
	}
}
