#include "pch.h"

FullPicture::FullPicture(const string _fileName)
	: UIBase()
{
	// UIComponentを生成することで自動で描画されるようになる
	mUIComponent = new UIComponent(this, eFullPicture);
	// テクスチャをセット
	mUIComponent->SetTexture(RENDERER->GetTexture(_fileName));

	mMoveSpeed = 0.1f;
}

void FullPicture::UpdateGameObject(float _deltaTime)
{
	if (mAlpha <= 0.0f || mAlpha >= 1.0f)
	{
		mMoveSpeed *= -1;
	}

	mAlpha -= mMoveSpeed;
}
