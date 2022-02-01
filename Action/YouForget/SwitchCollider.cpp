#include "pch.h"

// 静的メンバ　
Ground::alphaColor SwitchCollider::mLinkageColor = Ground::alphaColor::red;

// コンストラクタ
SwitchCollider::SwitchCollider(Switch* _owner,const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	:GameObject(_sceneTag, _objectTag)
	, mOwner(_owner)
{
	SetPosition(_owner->GetPosition());

	mTag = Tag::SwitchCenter;

	//スイッチ中心の当たり判定(ボックス)
	mSwitchBoxCollider = new BoxCollider(this, ColliderTag::switchTag, GetOnCollisionFunc());
	AABB Switchbox = { Vector3(-50.0f,-80.0f,0.0f),Vector3(50.0f,80.0f,100.0f) };
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
	Tag hitObjectTag = _hitObject.GetTag();

	// スイッチと当たった時かつ、スイッチフラグがfalseの時
	if (hitObjectTag == Tag::player && !Switch::mSwitchFlag)
	{
		// フラグをtrueにする
		Switch::mSwitchFlag = true;
	}

	// スイッチの色が
	switch (mOwner->GetSwitchColor())
	{
	case(Switch::switchColor::red):  // 赤だったら
		// 床と連携させる色を赤に設定
		mLinkageColor = Ground::alphaColor::red;
		break;
	case(Switch::switchColor::green):  // 緑だったら
		// 床と連携させる色を緑に設定
		mLinkageColor = Ground::alphaColor::green;
		break;
	case(Switch::switchColor::yellow):  // 黄色だったら
		// 床と連携させる色を黄色に設定
		mLinkageColor = Ground::alphaColor::yellow;
		break;
	default:
		break;
	}

	/*if (mOwner->GetSwitchColor() == Switch::switchColor::green)
	{
		printf("緑\n");
	}
	else
	{
		printf("赤\n");
	}*/
}
