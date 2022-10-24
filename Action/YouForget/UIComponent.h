#pragma once

/*
* UIクラスを管理し、スクリーン上に描画するクラス
*/
class UIComponent : public Component
{
public:
	// 手前に描画するか、奥に描画するか
	enum class UIDrawType :unsigned char
	{
		eNear,	// 手前側に描画
		eFar,	// 奥側に描画
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner">アタッチするゲームオブジェクトのポインタ</param>
	/// <param name="_drawOrder">コンポーネントの更新順番（数値が小さいほど早く更新される）</param>
	/// <param name="_uiType">UIを手前に描画するか奥に描画するか判別するタグ （ベースは手前側に描画）</param>
	UIComponent(class GameObject* _owner, const int _drawOrder, const UIDrawType _uiDrawType = UIDrawType::eNear);
	// デストラクタ
	~UIComponent();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="_shader">使用するシェーダークラスのポインタ</param>
	void Draw(class Shader* _shader);

private:
	class Texture* mTexture;	// テクスチャ
	
	UIDrawType mUIDrawType;		// UIのタイプ

	int mDrawOrder;				// 描画される順番（数値が少ないほど早く更新される）

	int mTextureWidth;			// テクスチャの横幅
	int mTextureHeight;			// テクスチャの縦幅

	bool mVisible;				// 描画を行うか

public://ゲッターセッター
	/// <summary>
	/// UIのタイプを取得
	/// </summary>
	/// <returns></returns>
	UIDrawType GetUIDrawType()const { return mUIDrawType; }

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