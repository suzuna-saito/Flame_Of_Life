#pragma once

// リザルトのベースクラス
class ResultBase :public SceneBase
{
public:
	// コンストラクタ
	ResultBase();
	// デストラクタ
	~ResultBase();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <returns>次のシーンのポインタを返す</returns>
	SceneBase* update() override;

	static bool mClearEndFlag; // エンドの分岐フラグ(true : クリア)

protected:
	// どのピースを取得したかを検索する
	void mSearch();
	// 次の画像を出す処理
	void mDrawUpdate();
	// 次のシーンに移るか、まだ画像を出すかUpdate処理
	void mResultUpdate();

	map<ItemNum, string> mPuzzles;	// 取得したパズルピースとUIを関連付ける

private:
	vector<string> mPictures;	// 描画する画像

	bool mDraw;					// 表示処理をするかどうか
	
	unsigned int mNum;			// 出す画像のナンバー

	class FullPicture* mNowDescription;	// いるか？
	class AButtonUI * mAButton;			// AボタンのUI
};
