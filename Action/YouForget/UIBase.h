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
	~UIBase() {};

protected:
	UIComponent* mUiComponent;	// UIの描画クラス

public:// ゲッター、セッター
	// 画像を描画するかしないかセットする true:描画する
	void SetThisVisible(bool _flag) { mUiComponent->SetVisible(_flag); }
};
