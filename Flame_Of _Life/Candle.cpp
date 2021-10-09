/*
@brief	インクルード
*/
#include "pch.h"

Candle::Candle(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, _objectTag)
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
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Player/Candle/Candle_2.gpmesh"));

	//ろうそくの当たり判定
	mSelfBoxCollider = new BoxCollider(this, ColliderTag::groundTag, GetOnCollisionFunc());
	AABB box = { Vector3(-1.0f,-1.0f,0.0f),Vector3(1.0f,1.0f,0.7f) };
	mSelfBoxCollider->SetObjectBox(box);

	// ろうそくの火を生成
	new FireObject(this, Vector3(3.0f, 3.0f, 3.0f), mTag);
}

//void Candle::UpdateGameObject(float _deltaTime)
//{
//	if (mFireFlag && !mDrawFireFlag)
//	{
//		
//
//		mDrawFireFlag = true;
//	}
//}
