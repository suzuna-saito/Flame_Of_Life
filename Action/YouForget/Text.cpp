#include "pch.h"

Text::Text(const string _fileName)
	: UIBase()
{
	// UIComponent�𐶐����邱�ƂŎ����ŕ`�悳���悤�ɂȂ�
	mUIComponent = new UIComponent(this, eText);
	// �e�N�X�`�����Z�b�g
	mUIComponent->SetTexture(RENDERER->GetTexture(_fileName));

	// GameObject�N���X�̕ϐ�������
	mPosition.y = -320.0f;	// �|�W�V����
}
