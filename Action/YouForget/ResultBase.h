#pragma once

/*
* リザルトの基底クラス
*/
class ResultBase :public SceneBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_nowScene">現在のシーンタイプ</param>
	ResultBase(const SceneType& _nowScene);
	// デストラクタ
	~ResultBase();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <returns>次のシーンのポインタ</returns>
	SceneBase* update() override;

	static bool mClearEndFlag;	// エンドの分岐フラグ(true:クリア)

protected:
	// どのアイテムを取っているか検索する
	void mSearch();
	// 次の画像を出す処理
	void mDrawUpdate();
	// 次のシーンに移るか、まだ画像を出すかUpdate処理
	void mResultUpdate();

	map<ItemNum, string> mPuzzlePieces;	// ピースと必要な画像データを関連付けて格納
	class PuzzleUI* mPuzzleUI;			// パズルのUI
private:
	/// <summary>
	/// 描画したい画像データを追加する
	/// </summary>
	/// <param name="_uiType">画像のUIタイプ</param>
	/// <param name="_filename">画像のファイル名</param>
	void AddPictureData(const UIBase::UIType _uiType, const string _filename);

	class Text* mTextUI;										// テキスト画像のUI

	unordered_multimap<UIBase::UIType, string> mPictureDatas;	// 描画したい画像データとその画像のUIタイプを関連付けて格納(キー重複OK)
	//vector<string> mGetPieces;								// プレイ中に取得したパズルピースの画像データを格納
	//// 描画する画像
	//vector<string> mDescription;
	//// 表示した画像をvectorに保存し、デストラクタでまとめて消す
	//vector <class FullPicture*> mDeleteDescription;

	//// 表示処理をするかどうか
	//bool mDraw;

	//// 出す画像のナンバー
	//unsigned int mNum;

	//// 今表示している画像
	//class FullPicture* mNowDescription;
	//// ボタンのUI
	//class AButtonUI* mAButton;

	//////ボタン画像のUI
	////ButtonUI* mButtonUI;
};
