#include "pch.h"

UIComponent::UIComponent(class GameObject* _owner, const int _drawOrder)
	: Component(_owner)
	, mDrawOrder(_drawOrder)
	, mTexture(nullptr)
	, mTextureWidth(0)
	, mTextureHeight(0)
	, mVisible(true)
{
	//レンダラーにポインターを送る
	RENDERER->AddUI(this);
}

UIComponent::~UIComponent()
{
	//レンダラーからポインタを削除する
	RENDERER->RemoveUI(this);
}

void UIComponent::Draw(Shader* _shader)
{
	// 画像情報が空じゃないかつ、オブジェクトが未更新状態じゃなかったら
	if (mTexture && mOwner->GetState() != State::Dead)
	{
		// スケールの更新
		Matrix4 scaleMatrix = Matrix4::CreateScale(
			static_cast<float>(mTextureWidth)* mOwner->GetScale().x,
			static_cast<float>(mTextureHeight)* mOwner->GetScale().y,
			1.0f);

		// スクリーン位置の平行移動
		Matrix4 transMat = Matrix4::CreateTranslation(
			Vector3(mOwner->GetPosition().x - (mTextureWidth * 0.0f),
				mOwner->GetPosition().y - (mTextureHeight * 0.0f),
				0.0f));

		// 行列を計算
		Matrix4 world = scaleMatrix * transMat;
		// uWorldTransformを設定
		_shader->SetMatrixUniform("uWorldTransform", world);
		// uAlphaを設定
		_shader->SetFloatUniform("uAlpha", mOwner->GetAlpha());

		// これからスロット名”GL_TEXTURE0″の設定をする
		glActiveTexture(GL_TEXTURE0);
		// テクスチャの割り当て
		glBindTexture(GL_TEXTURE_2D, mTexture->GetTextureID());
		// 描画
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}

void UIComponent::SetTexture(Texture* _texture)
{
	// テクスチャをセット
	mTexture = _texture;
	// 縦、横の長さを取得
	mTextureWidth = mTexture->GetWidth();
	mTextureHeight = mTexture->GetHeight();
}
