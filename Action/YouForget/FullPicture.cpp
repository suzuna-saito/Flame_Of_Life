#include "pch.h"

FullPicture::FullPicture(const string _fileName, const UIComponent::UIDrawType _uiDrawType)
	: UIBase()
{
	// UIComponentを生成することで自動で描画されるようになる
	mUIComponent = new UIComponent(this, eFullPicture, _uiDrawType);
	// テクスチャをセット
	mUIComponent->SetTexture(RENDERER->GetTexture(_fileName));
}