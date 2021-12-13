#include "pch.h"

ItemChara::ItemChara(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	: ItemBase(_sceneTag, _objectTag)
{
	//GameObjectメンバ変数の初期化
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	//Component基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Item/Chara.gpmesh"));

	//人型アイテムの当たり判定
	mSelfBoxCollider = new BoxCollider(this, ColliderTag::itemTag, GetOnCollisionFunc());
	AABB box = { Vector3(13.0f,-20.0f,0.0f),Vector3(-13.0f,16.5f,9.0f) };
	mSelfBoxCollider->SetObjectBox(box);
}


void ItemChara::UpdateGameObject(float _deltaTime)
{
	// フラグが上がっていたら
	if (mCollisionFlag && GetState() != Disabling)
	{
		// ステートをdisablにする
		SetState(State::Disabling);

		ItemBase::mItemCount--;
	}
}


void ItemChara::OnCollision(const GameObject& _hitObject)
{
	// 当たったのでフラグを上げる
	mCollisionFlag = true;

	// 描画をやめる
	mMeshComponent->SetVisible(false);
}
