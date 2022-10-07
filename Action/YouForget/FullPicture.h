#pragma once

/*
* 1920×1080サイズの画像を描画するクラス
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
};

