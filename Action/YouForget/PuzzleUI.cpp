#include "pch.h"

PuzzleUI::PuzzleUI(const string _fileName, const UIType _type)
	: UIBase()
	, mType(_type)
{
	// UIComponentを生成することで自動で描画されるようになる
	mUIComponent = new UIComponent(this, _type);
	// テクスチャをセット
	mUIComponent->SetTexture(RENDERER->GetTexture(_fileName));
}

void PuzzleUI::UpdateGameObject(float _deltaTime)
{
}