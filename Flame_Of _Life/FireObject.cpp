#include "pch.h"

// コンストラクタ
FireObject::FireObject(Candle* _owner, const Vector3& _size, const Tag& _objectTag)
	: GameObject(GetScene(), _objectTag)
	, mOwner(_owner)
	, MAddPos(160.0f)
{
	//GameObjectメンバ変数の初期化
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(mOwner->GetPosition());

	//生成したPlayerの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Player/Candle/Flame_plane.gpmesh"));

	//回転処理                        ↓回転する値
	float radian = Math::ToRadians(180.0f);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::UnitZ, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}

/*
更新処理
*/
void FireObject::UpdateGameObject(float _deltaTime)
{
	Vector3 tmp = mOwner->GetPosition();
	tmp.z += MAddPos;
	SetPosition(tmp);
}