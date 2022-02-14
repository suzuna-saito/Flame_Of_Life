#pragma once

class Sprite;

// リザルトのベースクラス
class ResultBase :public SceneBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_nowScene 現在のシーン
	*/
	ResultBase(const Scene& _nowScene);

	/*
	@fn	デストラクタ
	*/
	~ResultBase();

protected:
	// マップで取得したアイテムと説明を関連付ける
	map<ItemNum, string> mItemDescription;

	// 描画する画像
	vector<string> mDescription;
	// 表示した画像をvectorに保存し、デストラクタでまとめて消す
	vector <Sprite*> mDeleteDescription;

	// 次の画像を表示するか
	bool mNextFlag;
	// 最後の画像を表示し終わったか
	bool mEndFlag;
	// 表示処理をするかどうか
	bool mDraw;

	// 出す画像のナンバー
	unsigned int mNum;

	// 今表示している画像
	Sprite* mNowDescription;
	// 後ろの画像
	Sprite* mBackDescription;

	// どのアイテムを取っているか検索する
	void mSearch();
	// 次の画像を出す処理
	void mDrawUpdate();
	// 次のシーンに移るか、まだ画像を出すかUpdate処理
	void mResultUpdate();
};
