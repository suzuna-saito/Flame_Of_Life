/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_fileName 画像ファイルの名前
*/
Sprite::Sprite(const std::string _fileName)
	:GameObject(SceneBase::SceneType::eInit, Tag::UI )
{
	mSpriteComponent = new SpriteComponent(this);

	mSpriteTexture = RENDERER->GetTexture(_fileName);
	mSpriteComponent->SetTexture(mSpriteTexture);
}
