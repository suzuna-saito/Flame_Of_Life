#include "pch.h"

BackGround::BackGround(const Vector3 _pos, const BackGroundType _type)
	: GameObject()
{
	// MeshComponentを生成することで自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Books/Book_1.gpmesh"));

	//GameObjectメンバ変数の初期化
	SetScale(Vector3(10.0f, 10.0f, 10.0f));	// スケール
	SetPosition(_pos);						// ポジション
	mAlpha = 0.3f;							// α値

	// タイプ別で色を変更
	if (_type == BackGroundType::eBGtypeOne)
	{
		mColor = Vector3(1.3f, 1.3f, 1.3f);
	}
	else
	{
		mColor = Vector3 (0.68f, 0.85f, 0.9f);
	}
}