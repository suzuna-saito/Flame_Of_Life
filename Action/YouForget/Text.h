#pragma once

/*
* テキスト画像を描画するクラス
*/
class Text : public UIBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_fileName">画像ファイルの名前</param>
	Text(const string _fileName);
	// デストラクタ
	~Text() {};
};

