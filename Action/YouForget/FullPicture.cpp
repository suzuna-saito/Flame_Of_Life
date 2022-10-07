#include "pch.h"

FullPicture::FullPicture(const string _fileName)
	: UIBase()
{
	// UIComponent�𐶐����邱�ƂŎ����ŕ`�悳���悤�ɂȂ�
	mUIComponent = new UIComponent(this, mPosition, mScale, eFullPicture);

	// �e�N�X�`���𐶐�
	mUIComponent->SetTexture(RENDERER->GetTexture(_fileName));
}
