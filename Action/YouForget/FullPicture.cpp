#include "pch.h"

FullPicture::FullPicture(const string _fileName)
	: UIBase()
{
	// UIComponentを生成することで自動で描画されるようになる
	mUiComponent = new UIComponent(this, mPosition, mScale, 0);

	// テクスチャを生成
	mUiComponent->SetTexture(RENDERER->GetTexture(_fileName));
}
