#include "pch.h"

FullPicture::FullPicture(const string _fileName)
	: UIBase()
{
	// UIComponent�𐶐����邱�ƂŎ����ŕ`�悳���悤�ɂȂ�
	mUIComponent = new UIComponent(this,eFullPicture);
	// �e�N�X�`�����Z�b�g
	mUIComponent->SetTexture(RENDERER->GetTexture(_fileName));
}
