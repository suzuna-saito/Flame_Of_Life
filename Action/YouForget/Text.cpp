#include "pch.h"

Text::Text(const string _fileName)
	: UIBase()
{
	// UIComponentを生成することで自動で描画されるようになる
	mUIComponent = new UIComponent(this, mPosition, mScale, eText);

	// テクスチャを生成
	mUIComponent->SetTexture(RENDERER->GetTexture(_fileName));
}
