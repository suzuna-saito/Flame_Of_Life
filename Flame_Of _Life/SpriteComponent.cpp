/*
@file	SpriteComponent.h
@brief	画像データクラスを管理し、スクリーン上に描画するクラス
*/

/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_owner アタッチするゲームオブジェクトのポインタ
@param	_drawOrder 描画の順番（数値が小さいほど早く描画される）
*/
SpriteComponent::SpriteComponent(GameObject* _owner, int _drawOrder)
	: Component(_owner)
	, mTexture(nullptr)
	, mDrawOrder(_drawOrder)
	, mTextureWidth(0)
	, mTextureHeight(0)
	, mVisible(true)
{
	//レンダラーにポインターを送る
	RENDERER->AddSprite(this);
}

/*
@fn		デストラクタ
*/
SpriteComponent::~SpriteComponent()
{
	//レンダラーからポインタを削除する
	RENDERER->RemoveSprite(this);
}

/*
@brief	描画処理
@param _shader 使用するシェーダークラスのポインタ
*/
void SpriteComponent::Draw(Shader* _shader)
{
	//画像情報が空でないか、親オブジェクトが未更新状態でないか
	if (mTexture && mOwner->GetState() != State::Dead)
	{
		Matrix4 scaleMatrix = Matrix4::CreateScale(
			static_cast<float>(mTextureWidth),
			static_cast<float>(mTextureHeight),
			1.0f);

		Matrix4 world = scaleMatrix * mOwner->GetWorldTransform();

		_shader->SetMatrixUniform("uWorldTransform", world);


		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mTexture->GetTextureID());
		_shader->SetIntUniform("uSpriteTexture", 0);


		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}

/*
@fn		テクスチャをセットし縦横の長さを計算する
@param	_texture 使用するテクスチャのポインタ
*/
void SpriteComponent::SetTexture(Texture* _texture)
{
	mTexture = _texture;
	mTextureWidth = mTexture->GetWidth();
	mTextureHeight = mTexture->GetHeight();
}
