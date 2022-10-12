#pragma once

/*
* UIクラスを管理し、スクリーン上に描画するクラス
*/
class UIComponent : public Component
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner">アタッチするゲームオブジェクトのポインタ</param>
	/// <param name="_drawOrder">コンポーネントの更新順番（数値が小さいほど早く更新される）</param>
	UIComponent(class GameObject* _owner, const int _drawOrder);
	// デストラクタ
	~UIComponent();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="_shader">使用するシェーダークラスのポインタ</param>
	void Draw(class Shader* _shader);

private:
	class Texture* mTexture;	// テクスチャ

	int mDrawOrder;				// 描画される順番（数値が少ないほど早く更新される）

	int mTextureWidth;			// テクスチャの横幅
	int mTextureHeight;			// テクスチャの縦幅

	bool mVisible;				// 描画を行うか

public://ゲッターセッター
	/// <summary>
	/// 描画番号を取得
	/// </summary>
	/// <returns>描画される順番（数値が少ないほど早く更新される）</returns>
	int GetDrawOrder()const { return mDrawOrder; }

	/// <summary>
	/// 描画をするかどうかを取得する
	/// </summary>
	/// <returns>true : 描画する</returns>
	bool GetVisible() const { return mVisible; }

	/// <summary>
	/// テクスチャをセットし縦横の長さを計算する
	/// </summary>
	/// <param name="_texture">使用するテクスチャのポインタ</param>
	void SetTexture(class Texture* _texture);

	/// <summary>
	/// 描画をするかどうかを設定
	/// </summary>
	/// <param name="_visible">true : 描画する</param>
	void SetVisible(bool _visible) { mVisible = _visible; }
};