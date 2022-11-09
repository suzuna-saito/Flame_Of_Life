#include "pch.h"

// 静的メンバ変数の初期化
bool Switch::mFollowSwitchFlag = false;	// スイッチをおしているかどうか true:押している

Switch::Switch(const Vector3 _pos,const Ground::GroundColor _color)
	:GameObject(ObjTag::eGround)
{
	// MeshComponentを生成することで自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);

	//当たり判定
	mSelfBoxCollider = new BoxCollider(this, mTag, GetOnCollisionFunc());
	AABB box = { Vector3(14.5f,-21.5f,0.0f),Vector3(-14.5f,20.0f,9.0f) };
	mSelfBoxCollider->SetObjectBox(box);

	// GameObjectメンバ変数の初期化
	SetScale(Vector3(10.0f, 10.0f, 10.0f));	// スケール
	SetPosition(_pos);						// ポジション

	//// タグによってgpmeshを変更
	//switch (_color)
	//{
	//case switchColor::red:
	//	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Switch/RedSwitch.gpmesh"));
	//	break;
	//case switchColor::green:
	//	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Switch/GreenSwitch.gpmesh"));
	//	break;
	//default:
	//	break;
	//}

	// スイッチ中心当たり判定の生成
	mSwitchCenter = new SwitchCollider(this, ObjTag::eSwitchCenter, SceneBase::mIsSceneType, _color);
}

void Switch::UpdateGameObject(float _deltaTime)
{
	mAabb = mSelfBoxCollider->GetWorldBox();

}