/*
@brief	インクルード
*/
#include "pch.h"

// 静的メンバ変数

int Candle::mCandleCount = 0; // 火がついてるろうそくの本数

Candle::Candle(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, _objectTag)
	, mFireScele(Vector3(10.0f,10.0f,10.0f))
	, mFireFlag(false)
	, mDrawFireFlag(false)
{
	//GameObjectメンバ変数の初期化
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	//Component基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Candle/Candle_2.gpmesh"));

	//ろうそくの当たり判定
	mSelfBoxCollider = new BoxCollider(this, ColliderTag::candleTag, GetOnCollisionFunc());
	AABB box = { Vector3(-3.0f,-1.0f,0.0f),Vector3(3.0f,1.0f,10.0f) };
	mSelfBoxCollider->SetObjectBox(box);
}

/*
@fn		ろうそくのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void Candle::UpdateGameObject(float _deltaTime)
{
	if (mFireFlag && !mDrawFireFlag)
	{
		// ろうそくの火を生成
		new FireObject(this, mFireScele, mTag, GetScene());

		mDrawFireFlag = true;

		mCandleCount++;
	}
}

/*
@fn		ろうそくがヒットした時の処理
@param	_hitObject ヒットした対象のゲームオブジェクトのアドレス
*/
void Candle::OnCollision(const GameObject& _hitObject)
{
	mFireFlag = true;
}
