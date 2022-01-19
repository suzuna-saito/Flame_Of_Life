#include "pch.h"

// コンストラクタ
SwitchCollider::SwitchCollider(Switch* _owner,const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	:GameObject(_sceneTag, _objectTag)
	, mOwner(_owner)
{
	SetPosition(_owner->GetPosition());

	mTag = Tag::SwitchCenter;

	//スイッチ中心の当たり判定(ボックス)
	mSwitchBoxCollider = new BoxCollider(_owner, ColliderTag::switchTag, GetOnCollisionFunc());
	AABB Switchbox = { Vector3(2.0f,-4.0f,15.0f),Vector3(-2.0f,4.0f,16.0f) };
	mSwitchBoxCollider->SetObjectBox(Switchbox);
}

void SwitchCollider::UpdateGameObject(float _deltaTime)
{
	// スイッチのフラグをfalseに戻す
	Switch::mSwitchFlag = false;
}

void SwitchCollider::OnCollision(const GameObject& _hitObject)
{
	//ヒットしたオブジェクトのタグを取得
	mTag = _hitObject.GetTag();

	// スイッチと当たった時かつ、スイッチフラグがfalseの時
	if (mTag == Tag::Switch && !Switch::mSwitchFlag)
	{
		// フラグをtrueにする
		Switch::mSwitchFlag = true;
	}
}
