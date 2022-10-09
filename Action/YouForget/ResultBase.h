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
	/// <returns>次のシーンのタイプ</returns>
	SceneType update() override { return SceneType::eInit; }

	static bool mClearEndFlag;	// エンドの分岐フラグ(true:クリア)

protected:
	// どのパズルピースを取得しているか検索し、取得したデータは格納する
	void Search();	
	/// <summary>
	/// 取得数に応じてフラグを返す
	/// </summary>
	/// <returns>true : パズルピースを全て回収している</returns>
	bool Collected();

	/// <summary>
	/// 描画したい画像データを格納する
	/// </summary>
	/// <param name="_filename">画像のファイル名</param>
	/// <param name="_uiType">画像のUIタイプ</param>
	void StoresData(const string _filename, const int _uiType);
	/// <summary>
	/// mFileNamesに格納されているデータを一つずつ描画する
	/// </summary>
	/// <returns>true : 全て描画した</returns>
	bool mDrawUpdate();

	map<ItemNum, string> mPuzzlePieceDatas;	// ピースと必要な画像データを関連付けて格納
private:
	class Text* mNowDrawTextUI;				// 今描画しいているテキスト画像のUI

	map<string, int> mPictureDatas;			// 描画したい画像データとその画像のUIタイプを関連付けて格納
	vector<string> mFileNames;				// mPictureDatasにキーとして格納した全てのファイル名(描画したいファイル)
};
