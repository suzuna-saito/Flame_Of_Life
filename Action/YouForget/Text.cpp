#include "pch.h"

Text::Text(const string _fileName)
	: UIBase()
{
	// GameObject�N���X�̕ϐ�������
	mPosition.y = -320.0f;	// �|�W�V����

	// UIComponent�𐶐����邱�ƂŎ����ŕ`�悳���悤�ɂȂ�
	mUIComponent = new UIComponent(this, mPosition, mScale, eText);

	// �e�N�X�`���𐶐�
	mUIComponent->SetTexture(RENDERER->GetTexture(_fileName));
}
