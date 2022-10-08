#include "pch.h"

AButtonUI::AButtonUI()
	: UIBase()
	, mMaxScale(1.5f)
	, mMinScale(1.2f)
	, mAddScale(0.005f)
{
	// GameObjectクラスの変数初期化
	mPosition = Vector3(820.0f,-420.0f,0.0f);		// ポジション
	mScale = Vector3(mMaxScale, mMaxScale, 0.0f);	// スケール

	// UIComponentを生成することで自動で描画されるようになる
	mUIComponent = new UIComponent(this, mPosition, mScale);
	// テクスチャを生成
	mUIComponent->SetTexture(RENDERER->GetTexture("Assets/UI/ResultBase/Button2.png"));
}

void AButtonUI::UpdateGameObject(float _deltaTime)
{
	// mScaleが最小値より小さい、または、最大値より大きかったら
	if (mScale.x <= mMinScale || mScale.x >= mMaxScale)
	{
		mAddScale *= -1;	// 符号を変える
	}
	// スケール値にmAddScaleを足す
	mScale += Vector3(mAddScale, mAddScale, 0.0f);
	// スケール値をセット
	mUIComponent->SetScale(mScale);

}
