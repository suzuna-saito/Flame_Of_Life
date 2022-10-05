#pragma once

/*
* 画面の大きさにあった画像を描画するクラス
*/
class FullPicture : public UIBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_fileName">画像ファイルの名前</param>
	FullPicture(const string _fileName);
	// デストラクタ
	~FullPicture() {};

private:
	class Texture* mFullPictureTexture;	//テクスチャを生成
	class UIComponent* mUIComponent;	//SpriteComponentを生成

public:
	void SetThisVisible(bool _flag) { mUIComponent->SetVisible(_flag); }

	bool GetThisVisible() { return mUIComponent->GetVisible(); }
};

