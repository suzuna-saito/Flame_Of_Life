#include "pch.h"

// コンストラクタ
LegsCollider::LegsCollider(Player* _owner, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	:GameObject(_sceneTag, _objectTag)
	, mIsGround(false)
	, mOwner(_owner)
{
	//プレイヤー足元の当たり判定(ボックス)
	mLegsBoxCollider = new BoxCollider(_owner, ColliderTag::playerLegsTag, GetOnCollisionFunc());
	AABB Legsbox = { Vector3(750.0f,-750.0f,0.0f),Vector3(-750.0f,750.0f,300.0f) };
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
	// 接地フラグをtrueにする
	mIsGround = true;
	////ヒットしたオブジェクトのタグを取得
	//mTag = _hitObject.GetTag();

	//// 床と設置したとき
	//if (mTag == ground)
	//{
	//}
}
