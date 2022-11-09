#include "pch.h"

// 静的メンバの初期化
Ground::GroundColor SwitchCollider::mLinkageColor = Ground::GroundColor::eRed;

// コンストラクタ
SwitchCollider::SwitchCollider(Switch* _owner,const ObjTag& _objectTag, const SceneBase::SceneType _sceneTag, const Switch::switchColor _switchColor)
	:GameObject(ObjTag::eSwitchCenter)
	, mOwner(_owner)
{
	SetPosition(_owner->GetPosition());

	mTag = ObjTag::eSwitchCenter;

	//スイッチ中心の当たり判定(ボックス)
	mSwitchBoxCollider = new BoxCollider(this,mTag, GetOnCollisionFunc());
	AABB Switchbox = { Vector3(-70.0f,-100.0f,0.0f),Vector3(70.0f,100.0f,100.0f) };
	mSwitchBoxCollider->SetObjectBox(Switchbox);

	if (_switchColor == Switch::switchColor::red)
	{
		// 床と連携させる色を赤に設定
		mSwitchColor = Ground::GroundColor::eRed;
	}
	else
	{
		// 床と連携させる色を緑に設定
		mSwitchColor = Ground::GroundColor::eGreen;
	}
}

void SwitchCollider::UpdateGameObject(float _deltaTime)
{
	// スイッチのフラグをfalseに戻す
	Switch::mFollowSwitchFlag = false;
}

void SwitchCollider::OnCollision(const GameObject& _hitObject)
{
	//ヒットしたオブジェクトのタグを取得
	ObjTag hitObjectTag = _hitObject.GetTag();

	// スイッチと当たった時かつ、スイッチフラグがfalseの時
	if (hitObjectTag == ObjTag::ePlayerLegs && !Switch::mFollowSwitchFlag)
	{
		// フラグをtrueにする
		Switch::mFollowSwitchFlag = true;

		mLinkageColor = mSwitchColor;
	}
}
