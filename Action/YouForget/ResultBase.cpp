#include "pch.h"

// 静的メンバ変数の初期化
bool ResultBase::mClearEndFlag = true;	// エンドの分岐フラグ(true:クリア)

ResultBase::ResultBase(const SceneType& _nowScene)
	: SceneBase(_nowScene)
	, mNowDrawTextUI(nullptr)
{
	mIsSceneType = _nowScene;

	// AボタンのUIを生成
	new AButtonUI();
}

ResultBase::~ResultBase()
{
	// シーンを遷移する前に取得したパズルピースを0に戻す
	PuzzlePiece::mGetNumber.clear();
}

void ResultBase::Search()
{
	// 取得したパズルピース分回す
	decltype(mPuzzlePieceDatas)::iterator it;
	for (const auto& num : PuzzlePiece::mGetNumber)
	{
		// キーが一致するものを探す
		it = mPuzzlePieceDatas.find(num);

		// 一致したら
		if (it != mPuzzlePieceDatas.end())
		{
			// ピースの画像データ保存
			StoresData(mPuzzlePieceDatas[num], UIBase::UIType::ePuzzlePiece);
		}
	}
}

bool ResultBase::Collected()
{
	// 全てのピースを回収できてなかったら
	if (mPictureDatas.size() != mPuzzlePieceDatas.size())
	{
		// 取得したピースが1つ以下だったら
		if (mPictureDatas.size() <= 1)
		{
			// 回収出来なかった用のテキスト画像 1 を追加格納
			StoresData("Assets/UI/ResultBase/BadWord.png", UIBase::UIType::eText);
		}
		// 取得したピースが2つ以上だったら
		else
		{
			// 回収出来なかった用のテキスト画像 2 を追加格納
			StoresData("Assets/UI/ResultBase/BadWord2.png", UIBase::UIType::eText);
		}
		
		// クリアフラグをfalseにする
		mClearEndFlag = false;

		return false;
	}
	
	return true;
}

void ResultBase::StoresData(const string _filename, const int _uiType)
{
	// 描画したい画像データとその画像のUIタイプを関連付けて格納
	mPictureDatas[_filename] = _uiType;
	// キー（ファイル名）を格納
	mFileNames.emplace_back(_filename);
}

bool ResultBase::mDrawUpdate()
{
	// mFileNamesの中が空だったら
	if (mFileNames.empty())
	{
		// mNowDrawTextUIが空じゃなかったら
		if (mNowDrawTextUI != nullptr)
		{
			// 今描画しているテキストの描画をやめる
			mNowDrawTextUI->SetThisVisible(false);
		}
		// もう全て描画したのでtrueを返す
		return true;
	}

	// mPictureDatasの値がePuzzlePieceだった時
	if (mPictureDatas[mFileNames[0]] == UIBase::UIType::ePuzzlePiece)
	{
		// パズルピースを生成
		new PuzzleUI(mFileNames[0], UIBase::UIType::ePuzzlePiece);
	}
	// mPictureDatasの値がeTextだった時
	else if (mPictureDatas[mFileNames[0]] == UIBase::UIType::eText)
	{
		// mNowDrawTextUIが空じゃなかったら
		if (mNowDrawTextUI != nullptr)
		{
			// 今描画しているテキストの描画をやめる
			mNowDrawTextUI->SetThisVisible(false);
		}

		// テキスト画像を生成
		mNowDrawTextUI = new Text(mFileNames[0]);
	}

	// (もうすでに描画したファイルなので)mFileNamesの先頭要素を削除
	mFileNames.erase(mFileNames.begin());

	return false;
}