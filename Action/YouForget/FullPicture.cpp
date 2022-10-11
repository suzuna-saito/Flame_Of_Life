#include "pch.h"

FullPicture::FullPicture(const string _fileName)
	: UIBase()
{
	// UIComponent�𐶐����邱�ƂŎ����ŕ`�悳���悤�ɂȂ�
	mUIComponent = new UIComponent(this, eFullPicture);
	// �e�N�X�`�����Z�b�g
	mUIComponent->SetTexture(RENDERER->GetTexture(_fileName));

	mMoveSpeed = 0.1f;
}

void FullPicture::UpdateGameObject(float _deltaTime)
{
	if (mAlpha <= 0.0f || mAlpha >= 1.0f)
	{
		mMoveSpeed *= -1;
	}

	mAlpha -= mMoveSpeed;
}
