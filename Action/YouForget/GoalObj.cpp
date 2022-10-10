#include "pch.h"

// 静的メンバ変数
bool GoalObj::mGoalFlag = false; // ゴールしたかどうか

GoalObj::GoalObj(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::SceneType _sceneTag)
	: GameObject(_sceneTag, _objectTag)
{
	// ゴールしたかどうかフラグをfalseにする
	mGoalFlag = false;

	//GameObjectメンバ変数の初期化
	mTag = _objectTag;   // オブジェクトタグ
	SetScale(_size);     // オブジェクトサイズ
	SetPosition(_pos);   // オブジェクトのポジション

	// エフェクト
	new GoalEffect(this);

	//ろうそくの当たり判定
	mSelfBoxCollider = new BoxCollider(this, ColliderTag::candleTag, GetOnCollisionFunc());
	AABB box = { Vector3(-50.0f,-10.0f,-50.0f),Vector3(50.0f,10.0f,50.0f) };
	mSelfBoxCollider->SetObjectBox(box);
}

/*
@fn		ろうそくのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void GoalObj::UpdateGameObject(float _deltaTime)
{
}

/*
@fn		ろうそくがヒットした時の処理
@param	_hitObject ヒットした対象のゲームオブジェクトのアドレス
*/
void GoalObj::OnCollision(const GameObject& _hitObject)
{
	// ゴールしたかどうかフラグをtrueにする
	mGoalFlag = true;
}
