/*
@brief	インクルード
*/
#include "pch.h"
#include <iostream>

// 静的メンバ変数
float Switch::mDistance = 0.0f;
bool Switch::mSwitchFlag = false;
Switch::switchColor Switch::mSwitchColor = Switch::switchColor::red;

Switch::Switch(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag, const switchColor& _color)
	:GameObject(_sceneTag, _objectTag)
	/*, mRedSwitchFlag(false)
	, mGreenSwitchFlag(false)
	, mYellowSwitchFlag(false)*/
{
	//GameObjectメンバ変数の初期化
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	// スイッチの色を設定
	mSwitchColor = _color;
	//mSwitchColor = _tag;

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
	AABB box = { Vector3(14.0f,-20.0f,0.0f),Vector3(-14.0f,16.5f,9.0f) };
	mSelfBoxCollider->SetObjectBox(box);

	// スイッチ中心当たり判定の生成
	mSwitchCenter = new SwitchCollider(this, _objectTag, _sceneTag);
}

void Switch::UpdateGameObject(float _deltaTime)
{
	mAabb = mSelfBoxCollider->GetWorldBox();

	// スイッチを押している状態だったら
	/*if (mSwitchFlag)
	{
		switch (mSwitchColor)
		{
		case(Ground::alphaColor::red):

		default:
			break;
		}
	}*/

}

void Switch::OnCollision(const GameObject& _hitObject)
{
}
