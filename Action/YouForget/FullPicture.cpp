#include "pch.h"

FullPicture::FullPicture(const string _fileName)
	: UIBase()
{
	// UIComponentを生成することで自動で描画されるようになる
	mUIComponent = new UIComponent(this, mPosition, mScale, eFullPicture);

	// テクスチャを生成
	mUIComponent->SetTexture(RENDERER->GetTexture(_fileName));
}
