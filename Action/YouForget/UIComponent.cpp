/*
@file  SpriteComponent.h
@brief 画像データクラスを管理し、スクリーン上に描画するクラス
*/

/*
@brief インクルード
*/
#include "pch.h"

//UIのID、カウント用の初期化
int UIComponent::mUIid = 0;

/*
@fn	   コンストラクタ
@param _owner アタッチするゲームオブジェクトのポインタ
@param _drawOrder 描画の順番（数値が小さいほど早く描画される）
*/
UIComponent::UIComponent(GameObject* _owner, const Vector3 _pos, const Vector3 _scale, int _drawOrder)
	: Component(_owner)
	, mTexture(nullptr)
	, mDrawOrder(_drawOrder)
	, mTextureWidth(0)
	, mTextureHeight(0)
	, mVisible(true)
	, mMyUIid(mUIid)
	, mScale(_scale)
	, mPos(_pos)
{
	mUIid++;
	//レンダラーにポインターを送る
	RENDERER->AddUI(this);
}

/*
@fn	デストラクタ
*/
UIComponent::~UIComponent()
{
	mUIid--;
	//レンダラーからポインタを削除する
	RENDERER->RemoveUI(this);
}

/*
@fn		描画処理
@param	_shader 使用するシェーダークラスのポインタ
*/
void UIComponent::Draw(Shader* _shader, const Vector3& _Pos, const Vector3 _scale)
{
	//画像情報が空でないか、親オブジェクトが未更新状態でないか
	if (mTexture && mOwner->GetState() != State::Dead)
	{
		Matrix4 scaleMatrix = Matrix4::CreateScale(
			static_cast<float>(mTextureWidth)* _scale.x,
			static_cast<float>(mTextureHeight)* _scale.y,
			1.0f);

		// スクリーン位置の平行移動
		Matrix4 transMat = Matrix4::CreateTranslation(
			Vector3(_Pos.x - (mTextureWidth * 0.0f),
				_Pos.y - (mTextureHeight * 0.0f), 0.0f));

		Matrix4 world = scaleMatrix * transMat;

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
void UIComponent::SetTexture(Texture* _texture)
{
	mTexture = _texture;
	mTextureWidth = mTexture->GetWidth();
	mTextureHeight = mTexture->GetHeight();
}
