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
ResultBase::ResultBase()
	:SceneBase()
	, mPictures()
	//, mDeleteDescription()
	, mDraw(false)
	, mNowDescription(nullptr)
	, mAButton(nullptr)
	, mNum(0)
{
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

/*
@fn	現在のシーン時に毎フレーム更新処理をする
*/
SceneBase* ResultBase::update()
{
	return nullptr;
}

void ResultBase::mSearch()
{
	// イテレーター
	decltype(mPuzzles)::iterator it;

	// 取得したアイテム分回す
	for (const auto& num : ItemBase::mGetNumber)
	{
		// 探す
		it = mPuzzles.find(num);

		// 見つかった
		if (it != mPuzzles.end())
		{
			// mDescriptionに見つかった分だけ保存
			mPictures.push_back(mPuzzles[num]);
		}
	}

	// 全てのピースを回収できてなかったら
	if (SceneBase::mIsScene != SceneType::eGameClear &&
		mPictures.size() != 3)
	{
		mPictures.push_back("Assets/UI/ResultBase/BadWord.png");
		mClearEndFlag = false;
	}
	else
	{
		// シーンによって更に画像を追加
		switch (SceneBase::mIsScene)
		{
		case SceneType::eFirstResult:
			mPictures.push_back("Assets/UI/FirstResult/Word_1.png");
			mPictures.push_back("Assets/UI/FirstResult/Word_2.png");
			break;
		case SceneType::eSecondResult:
			mPictures.push_back("Assets/UI/SecondResult/Word_1.png");
			mPictures.push_back("Assets/UI/SecondResult/Word_2.png");
			break;
		case SceneType::eThirdResult:
			mPictures.push_back("Assets/UI/ThirdResult/Word_1.png");
			mPictures.push_back("Assets/UI/ThirdResult/Word_2.png");
			break;
		case SceneType::eGameClear:
			if (mClearEndFlag)
			{
				mPictures.push_back("Assets/UI/EndResult/Clear_2.png");
				mPictures.push_back("Assets/UI/EndResult/Clear_3.png");
			}
			break;
		default:
			break;
		}
	}
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
		if (mNum == mPictures.size())
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
			mNowDescription = new FullPicture(mPictures[mNum]);
			// 一度newしたら、mDrawをfalseにする。
			mDraw = false;

			++mNum;
		}
	}

	
	if (mAButton == nullptr && SceneBase::mIsScene != SceneType::eGameClear)
	{
		mAButton = new AButtonUI();
	}
}