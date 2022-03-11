#include "pch.h"

BackGround::BackGround(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag,const int _type)
	:GameObject(_sceneTag, _objectTag)
	, mType(_type)
{
	//GameObjectメンバ変数の初期化
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	// Component基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Books/Book_1.gpmesh"));

	if (mType == 35)
	{
		// 色を設定
		mColor = Vector3(1.3f, 1.3f, 1.3f);
		// 透明度を設定
		mAlpha = 0.3f;
	}
	else
	{
		// 色を設定
		mColor = Vector3 (0.68f, 0.85f, 0.9f);
		// 透明度を設定
		mAlpha = 0.3f;
	}
	

}
