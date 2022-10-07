#include "pch.h"

PuzzleUI::PuzzleUI(const string _fileName, const UIType _type)
	: UIBase()
	, mType(_type)
{
	// UIComponent�𐶐����邱�ƂŎ����ŕ`�悳���悤�ɂȂ�
	mUIComponent = new UIComponent(this, mPosition, mScale, _type);

	// �e�N�X�`���𐶐�
	mUIComponent->SetTexture(RENDERER->GetTexture(_fileName));
}

void PuzzleUI::UpdateGameObject(float _deltaTime)
{
}