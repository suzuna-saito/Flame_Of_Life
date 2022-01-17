/*
@brief	インクルード
*/
#include "pch.h"

// 静的メンバ変数
float Switch::mDistance = 0.0f;
bool Switch::mSwitchFlag = false;
Ground::alphaColor Switch::mSwitchColor = Ground::alphaColor::red;


Switch::Switch(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag,const Ground::alphaColor& _tag)
	:GameObject(_sceneTag, _objectTag)
{
	//GameObjectメンバ変数の初期化
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	mSwitchColor = _tag;

	//Component基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);

	// タグによってgpmeshを変更
	switch (_tag)
	{
	case Ground::alphaColor::red:
		//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
		mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Switch/RedSwitch.gpmesh"));
		break;
	case Ground::alphaColor::green:
		//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
		mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Switch/GreenSwitch.gpmesh"));
		break;
	case Ground::alphaColor::yellow:
		break;
	default:
		break;
	}

	//当たり判定
	mSelfBoxCollider = new BoxCollider(this, ColliderTag::groundTag, GetOnCollisionFunc());
	AABB box = { Vector3(13.0f,-20.0f,0.0f),Vector3(-13.0f,16.5f,9.0f) };
	mSelfBoxCollider->SetObjectBox(box);
}

void Switch::UpdateGameObject(float _deltaTime)
{
	mAabb = mSelfBoxCollider->GetWorldBox();

	//// プレイヤーと、スイッチの距離を計算
	//if (Player::mGetPos().x >= mPosition.x)  // プレイヤーの値の方が大きければ
	//{
	//	mDistance = Player::mGetPos().x - mPosition.x;
	//}
	//else
	//{
	//	mDistance = mPosition.x - Player::mGetPos().x ;
	//}


	//// mDistance がマイナスだったら
	//if (mDistance < 0.0f)
	//{
	//	// 正の数にする
	//	mDistance *= -1;
	//}


}

void Switch::mSubtraction(Vector3 _pPos, Vector3 _sPos)
{
	//(_pPos.x - _sPos.x)* (_pPos.x - _sPos.x);

	
}

void Switch::OnCollision(const GameObject& _hitObject)
{
}
