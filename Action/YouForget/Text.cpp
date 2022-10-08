#include "pch.h"

Text::Text(const string _fileName)
	: UIBase()
{
	// GameObjectクラスの変数初期化
	mPosition.y = -320.0f;	// ポジション

	// UIComponentを生成することで自動で描画されるようになる
	mUIComponent = new UIComponent(this, mPosition, mScale, eText);

	// テクスチャを生成
	mUIComponent->SetTexture(RENDERER->GetTexture(_fileName));
}
