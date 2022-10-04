/*
@brief	インクルード
*/
#include "pch.h"

bool ResultBase::mTrueEndFlag = true;
//Sprite* ResultBase::mEndSprite;

/*
@fn		コンストラクタ
@param	_nowScene 現在のシーン
*/
ResultBase::ResultBase(const SceneType& _nowScene)
	:SceneBase()
	, mDescription()
	, mDeleteDescription()
	, mDraw(false)
	, mNowDescription(nullptr)
	, mButtonSprite(nullptr)
	, mNum(0)
{
	SetScene(_nowScene);

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

	// 消したいデータが入っていたら
	int size = mDeleteDescription.size();
	for (int i = 0; i < size; i++)
	{
		delete mDeleteDescription[i];
	}

	delete mButtonSprite;
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
	decltype(mItemDescription)::iterator it;

	// 取得したアイテム分回す
	for (const auto& num : ItemBase::mGetNumber)
	{
		// 探す
		it = mItemDescription.find(num);

		// 見つかった
		if (it != mItemDescription.end())
		{
			// mDescriptionに見つかった分だけ保存
			mDescription.push_back(mItemDescription[num]);
		}
	}

	// 全てのピースを回収できてなかったら
	if (GetScene() != SceneType::eGameClear &&
		mDescription.size() != 3)
	{
		mDescription.push_back("Assets/UI/ResultBase/BadWord.png");
		mTrueEndFlag = false;
	}
	else
	{
		// シーンによって更に画像を追加
		switch (GetScene())
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
			if (mTrueEndFlag)
			{
				mDescription.push_back("Assets/UI/EndResult/Clear_2.png");
				mDescription.push_back("Assets/UI/EndResult/Clear_3.png");
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

	if (GetScene() == SceneType::eGameClear)
	{
		if (GetScene() == SceneType::eGameClear && mSprite != nullptr)
		{
			mSprite->SetThisVisible(false);
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
			mNowDescription = new Sprite(mDescription[mNum]);
			// 一度newしたら、mDrawをfalseにする。
			mDraw = false;

			++mNum;

			// デストラクタで削除するようにvectorに保存しておく
			mDeleteDescription.push_back(mNowDescription);
		}
	}

	
	if (mButtonSprite == nullptr && GetScene() != SceneType::eGameClear)
	{
		mButtonSprite = new Sprite("Assets/UI/ResultBase/Button.png");
	}
}

