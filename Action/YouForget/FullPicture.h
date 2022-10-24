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
	/// <param name="_uiDrawType">画像を手間に描画するか奥に描画するか（ベースは手前側）</param>
	FullPicture(const string _fileName, const UIComponent::UIDrawType _uiDrawType = UIComponent::UIDrawType::eNear);
	// デストラクタ
	~FullPicture() {};
};