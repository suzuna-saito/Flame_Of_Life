#include "pch.h"

AButtonUI::AButtonUI()
	: UIBase()
	, mAddScale(-0.01f)
{
	// GameObjectクラスの変数初期化
	mPosition = Vector3(800.0f,0.0f,-400.0f);	// ポジション
	mScale = Vector3(2.0f, 2.0f, 0.0f);			// スケール

	// UIComponentを生成することで自動で描画されるようになる
	mUiComponent = new UIComponent(this, mPosition, mScale);
	// テクスチャを生成
	mUiComponent->SetTexture(RENDERER->GetTexture("Assets/UI/ResultBase/Button2.png"));
}

void AButtonUI::UpdateGameObject(float _deltaTime)
{
	// mScaleが2.0fより小さい、または、2.5fより大きかったら
	if (mScale.x <= 2.0f || mScale.x >= 2.5f)
	{
		mAddScale *= -1;	// 符号を変える
	}
	// スケール値にmAddScaleを足す
	mScale += Vector3(mAddScale, mAddScale, 0.0f);
	// スケール値をセット
	mUiComponent->SetScale(mScale);

}
