#include "pch.h"

FullPicture::FullPicture(const string _fileName)
	: UIBase()
{
	// UIComponent�𐶐����邱�ƂŎ����ŕ`�悳���悤�ɂȂ�
	mUiComponent = new UIComponent(this, mPosition, mScale, 0);

	// �e�N�X�`���𐶐�
	mUiComponent->SetTexture(RENDERER->GetTexture(_fileName));
}
