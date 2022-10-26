/*
@brief	インクルード
*/
#include "pch.h"

// 静的メンバ変数
// スイッチをおしているかどうか
bool Switch::mSwitchFlag = false;

Switch::Switch(const Vector3& _pos, const Vector3& _size, const CollisionTag& _objectTag, const SceneBase::SceneType _sceneTag, const switchColor& _color)
	:GameObject(_sceneTag, _objectTag)
{
	//GameObjectメンバ変数の初期化
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	// スイッチの色を設定
	mSwitchColor = _color;

	//Component基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);

	// タグによってgpmeshを変更
	switch (_color)
	{
	case switchColor::red:
		//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
		mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Switch/RedSwitch.gpmesh"));
		/*mRedSwitchFlag = true;*/
		break;
	case switchColor::green:
		//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
		mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Switch/GreenSwitch.gpmesh"));
		/*mGreenSwitchFlag = true;*/
		break;
	case switchColor::yellow:
		break;
	default:
		break;
	}

	//当たり判定
	mSelfBoxCollider = new BoxCollider(this, ColliderTag::groundTag, GetOnCollisionFunc());
	AABB box = { Vector3(14.5f,-21.5f,0.0f),Vector3(-14.5f,20.0f,9.0f) };
	mSelfBoxCollider->SetObjectBox(box);

	// スイッチ中心当たり判定の生成
	mSwitchCenter = new SwitchCollider(this, CollisionTag::SwitchCenter, _sceneTag);

}

void Switch::UpdateGameObject(float _deltaTime)
{
	mAabb = mSelfBoxCollider->GetWorldBox();

}

void Switch::OnCollision(const GameObject& _hitObject)
{
}
