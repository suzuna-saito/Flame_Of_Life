#pragma once

/*
* UI関連の基底クラス
*/
class UIBase : public GameObject
{
public:
	// コンストラクタ
	UIBase();
	// デストラクタ
	virtual ~UIBase() {};

	//　UIの種類（描画したい順）
	enum UIType :unsigned char
	{
		eFullPicture,	// 1920×1080サイズのUI
		ePuzzleBase,	// パズルの基盤
		ePuzzlePiece,	// パズルのピース
		eText,			// テキスト
		eAButton,		// Aボタン
	};

protected:
	class UIComponent* mUIComponent;	// UIの描画クラス

public:// ゲッター、セッター
	// 画像を描画するかしないかセットする true:描画する
	void SetThisVisible(bool _flag) { mUIComponent->SetVisible(_flag); }
};
