#include "pch.h"

/*
@fn		コンストラクタ
@param	_fileName 画像ファイルの名前
*/
FullPicture::FullPicture(const string _fileName)
	:UIBase(Vector2::Zero, _fileName, SceneBase::mIsScene,Tag::UI,1.0f)
{
	mUIComponent = new UIComponent(this);

	mFullPictureTexture = RENDERER->GetTexture(_fileName);
	mUIComponent->SetTexture(mFullPictureTexture);
}
