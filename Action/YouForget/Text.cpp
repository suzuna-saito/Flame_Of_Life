#include "pch.h"

Text::Text(const string _fileName)
	: UIBase()
{
	// UIComponentを生成することで自動で描画されるようになる
	mUIComponent = new UIComponent(this, eText);
	// テクスチャをセット
	mUIComponent->SetTexture(RENDERER->GetTexture(_fileName));

	// GameObjectクラスの変数初期化
	mPosition.y = -320.0f;	// ポジション
}
