#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_fileName �摜�t�@�C���̖��O
*/
FullPicture::FullPicture(const string _fileName)
	:UIBase(Vector2::Zero, _fileName, SceneBase::mIsScene,Tag::UI,1.0f)
{
	mUIComponent = new UIComponent(this);

	mFullPictureTexture = RENDERER->GetTexture(_fileName);
	mUIComponent->SetTexture(mFullPictureTexture);
}
