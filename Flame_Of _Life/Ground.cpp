/*
@brief	インクルード
*/
#include "pch.h"


Ground::Ground(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	:GameObject(_sceneTag, _objectTag)
	, mAlphaCount(0)
	, mAlphaAdd(0.01f)
	, mAlphaSub(-0.01f)
	, mAlphaChange(true)
{
	//GameObjectメンバ変数の初期化
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	mColor = Vector3(0.5f,0.3f,0.7f);

	//Component基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Environment/Books/Book_1.gpmesh"));
	//mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Environment/Carpets/Carpet.gpmesh"));

	//地面の当たり判定
	mSelfBoxCollider = new BoxCollider(this, ColliderTag::groundTag, GetOnCollisionFunc());
	AABB box = { Vector3(13.0f,-20.0f,0.0f),Vector3(-13.0f,16.5f,9.0f) };
	mSelfBoxCollider->SetObjectBox(box);

	////回転処理                        ↓回転する値
	//float radian = Math::ToRadians(180.0f);
	//Quaternion rot = this->GetRotation();
	//Quaternion inc(Vector3::UnitZ, radian);
	//Quaternion target = Quaternion::Concatenate(rot, inc);
	//SetRotation(target);
}

void Ground::UpdateGameObject(float _deltaTime)
{
	mAabb = mSelfBoxCollider->GetWorldBox();
	if (mAlphaChange)
	{
		mAlpha += mAlphaSub;
	}
	else
	{
		mAlpha += mAlphaAdd;
	}

	if (mAlpha <= 0.0f)
	{
		mAlphaChange = false;
	}
	else if (mAlpha >= 1.0f)
	{
		mAlphaChange = true;
	}

	/*if (mAlphaChange)
	{
		mAlphaSub *= -1.0f;
	}*/

}
