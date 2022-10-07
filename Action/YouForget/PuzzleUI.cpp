#include "pch.h"

PuzzleUI::PuzzleUI(const string _fileName, const UIType _type)
	: UIBase()
	, mType(_type)
{
	// UIComponentを生成することで自動で描画されるようになる
	mUIComponent = new UIComponent(this, mPosition, mScale, _type);

	// テクスチャを生成
	mUIComponent->SetTexture(RENDERER->GetTexture(_fileName));
}

void PuzzleUI::UpdateGameObject(float _deltaTime)
{
}