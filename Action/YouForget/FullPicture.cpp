#include "pch.h"

FullPicture::FullPicture(const string _fileName, const UIComponent::UIDrawType _uiDrawType)
	: UIBase()
{
	// UIComponent�𐶐����邱�ƂŎ����ŕ`�悳���悤�ɂȂ�
	mUIComponent = new UIComponent(this, eFullPicture, _uiDrawType);
	// �e�N�X�`�����Z�b�g
	mUIComponent->SetTexture(RENDERER->GetTexture(_fileName));
}