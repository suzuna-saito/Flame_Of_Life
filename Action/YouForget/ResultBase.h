#pragma once

class ButtonUI;

// リザルトのベースクラス
class ResultBase :public SceneBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_nowScene 現在のシーン
	*/
	ResultBase(const SceneType& _nowScene);

	/*
	@fn	デストラクタ
	*/
	~ResultBase();

	/*
	@fn	タイトルシーン時に毎フレーム更新処理をする
	*/
	SceneBase* update() override;

	// エンドの分岐フラグ
	static bool mTrueEndFlag;

	// @@@
	//static Sprite* mEndSprite;

protected:
	
	// マップで取得したアイテムと説明を関連付ける
	map<ItemNum, string> mItemDescription;

	// どのアイテムを取っているか検索する
	void mSearch();
	// 次の画像を出す処理
	void mDrawUpdate();
	// 次のシーンに移るか、まだ画像を出すかUpdate処理
	void mResultUpdate();

private:

	// 描画する画像
	vector<string> mDescription;
	// 表示した画像をvectorに保存し、デストラクタでまとめて消す
	vector <class FullPicture*> mDeleteDescription;

	// 表示処理をするかどうか
	bool mDraw;

	// 出す画像のナンバー
	unsigned int mNum;

	// 今表示している画像
	class FullPicture* mNowDescription;
	// ボタンの画像
	class FullPicture* mButtonSprite;

	////ボタン画像のUI
	//ButtonUI* mButtonUI;
};
