/*
@brief	インクルード
*/
#include "pch.h"

bool ResultBase::mClearEndFlag = true;
//Sprite* ResultBase::mEndSprite;

/*
@fn		コンストラクタ
@param	_nowScene 現在のシーン
*/
ResultBase::ResultBase(const SceneType& _nowScene)
	:SceneBase(_nowScene)
	, mDescription()
	, mGetPieces()
	//, mDeleteDescription()
	, mDraw(false)
	, mNowDescription(nullptr)
	, mPuzzleUI(nullptr)
	, mAButton(nullptr)
	, mNum(0)
{
	mIsScene = _nowScene;


	/*if (GetScene() == Scene::gameClear)
	{
		if (mTrueEndFlag)
		{
			mSprite = new Sprite("Assets/UI/EndResult/Clear_1.png");
		}
		else
		{
			mSprite = new Sprite("Assets/UI/EndResult/Clear_4.png");
		}
	}*/
}

/*
@fn	デストラクタ
*/
ResultBase::~ResultBase()
{
	// 取得したアイテムの中にデータが入っていれば
	if (ItemBase::mGetNumber.size() != 0)
	{
		ItemBase::mGetNumber.clear();
	}
}

SceneBase* ResultBase::update()
{
	return nullptr;
}

void ResultBase::mSearch()
{
	// 取得したパズルピース分回す
	decltype(mPuzzlePieces)::iterator it;
	for (const auto& num : ItemBase::mGetNumber)
	{
		// キーが一致するものを探す
		it = mPuzzlePieces.find(num);

		// 見つかったら
		if (it != mPuzzlePieces.end())
		{
			// ピースの画像データ保存
			AddPictureData(UIBase::UIType::ePuzzlePiece, mPuzzlePieces[num]);
		}
	}

	// 全てのピースを回収できてなかったら
	if (mPictureDatas.size() != mPuzzlePieces.size())
	{
		mDescription.push_back("Assets/UI/ResultBase/BadWord.png");
		mClearEndFlag = false;
	}
	else
	{
		// シーンによって更に画像を追加
		switch (SceneBase::mIsScene)
		{
		case SceneType::eFirstResult:
			mDescription.push_back("Assets/UI/FirstResult/Word_1.png");
			mDescription.push_back("Assets/UI/FirstResult/Word_2.png");
			break;
		case SceneType::eSecondResult:
			mDescription.push_back("Assets/UI/SecondResult/Word_1.png");
			mDescription.push_back("Assets/UI/SecondResult/Word_2.png");
			break;
		case SceneType::eThirdResult:
			mDescription.push_back("Assets/UI/ThirdResult/Word_1.png");
			mDescription.push_back("Assets/UI/ThirdResult/Word_2.png");
			break;
		case SceneType::eGameClear:
			if (mClearEndFlag)
			{
				mDescription.push_back("Assets/UI/EndResult/Clear_2.png");
				mDescription.push_back("Assets/UI/EndResult/Clear_3.png");
			}
			break;
		default:
			break;
		}
	}

	// @@@
	// 全てのピースを回収できてなかったら
	//if (SceneBase::mIsScene != SceneType::eGameClear &&
	//	mGetPieces.size() != mPuzzlePieces.size())
	//{
	//	mDescription.push_back("Assets/UI/ResultBase/BadWord.png");
	//	mClearEndFlag = false;
	//}
	//else
	//{
	//	 シーンによって更に画像を追加
	//	switch (SceneBase::mIsScene)
	//	{
	//	case SceneType::eFirstResult:
	//		mDescription.push_back("Assets/UI/FirstResult/Word_1.png");
	//		mDescription.push_back("Assets/UI/FirstResult/Word_2.png");
	//		break;
	//	case SceneType::eSecondResult:
	//		mDescription.push_back("Assets/UI/SecondResult/Word_1.png");
	//		mDescription.push_back("Assets/UI/SecondResult/Word_2.png");
	//		break;
	//	case SceneType::eThirdResult:
	//		mDescription.push_back("Assets/UI/ThirdResult/Word_1.png");
	//		mDescription.push_back("Assets/UI/ThirdResult/Word_2.png");
	//		break;
	//	case SceneType::eGameClear:
	//		if (mClearEndFlag)
	//		{
	//			mDescription.push_back("Assets/UI/EndResult/Clear_2.png");
	//			mDescription.push_back("Assets/UI/EndResult/Clear_3.png");
	//		}
	//		break;
	//	default:
	//		break;
	//	}
	//}
}

void ResultBase::mDrawUpdate()
{
	// 次の説明を出すようにする
	mDraw = true;

	if (SceneBase::mIsScene == SceneType::eGameClear)
	{
		if (SceneBase::mIsScene == SceneType::eGameClear && mFullPicture != nullptr)
		{
			mFullPicture->SetThisVisible(false);
		}

		if (mNowDescription != nullptr)
		{
			mNowDescription->SetThisVisible(false);
		}
	}
}

void ResultBase::mResultUpdate()
{
	// mDrawがtrueの時
	if (mDraw)
	{
		if (mNum == mDescription.size())
		{
			// シーン遷移フラグをtrueにする
			mGameSceneFlag = true;
		}
		else
		{
			// @@@
			if (mNum == 4)
			{
				mNowDescription->SetThisVisible(false);
			}
			// 新しい画像を出す
			mPuzzleUI = new PuzzleUI(mGetPieces[mNum], UIBase::UIType::ePuzzlePiece);
			//mNowDescription = new FullPicture(mDescription[mNum]);
			// 一度newしたら、mDrawをfalseにする。
			mDraw = false;

			++mNum;

			//// デストラクタで削除するようにvectorに保存しておく
			//mDeleteDescription.push_back(mNowDescription);
		}
	}


	if (mAButton == nullptr && SceneBase::mIsScene != SceneType::eGameClear)
	{
		mAButton = new AButtonUI();
	}
}

void ResultBase::AddPictureData(const UIBase::UIType _uiType, const string _filename)
{
	// 描画したい画像データとその画像のUIタイプを関連付けて格納
	mPictureDatas.insert(pair<UIBase::UIType, string>(_uiType, _filename));
}