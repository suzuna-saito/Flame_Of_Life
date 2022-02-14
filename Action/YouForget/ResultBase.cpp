/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_nowScene 現在のシーン
*/
ResultBase::ResultBase(const Scene& _nowScene)
	:SceneBase()
	, mDescription()
	, mDeleteDescription()
	, mNextFlag(false)
	, mEndFlag(false)
	, mDraw(false)
	, mNowDescription(nullptr)
	, mNum(0)
{
	SetScene(_nowScene);

	// 一番後ろの画像
	mBackDescription = new Sprite("Assets/UI/BackPicture.png");

	// シーンによって最後に描画する画像を変える
	if (_nowScene == Scene::thirdResult)
	{
		mEndSprite = "Assets/UI/End.png";
	}
	else
	{
		mEndSprite = "Assets/UI/TitleB.png";
	}
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

	delete mSprite;
	delete mBackDescription;
}

void ResultBase::mDrawUpdate()
{
	// 最後の説明まで言ってたら
	if (mEndFlag)
	{
		// シーン遷移フラグをtrueにする
		mGameSceneFlag = true;
	}

	// 最後の説明まで描画できてなかったら
	if (mNum < mDescription.size())
	{
		// 次の説明を出すようにする
		mDraw = true;
	}
	else
	{
		mEndFlag = true;
	}
}

void ResultBase::mResultUpdate()
{
	// 保存した分回す
	if (mNum < mDescription.size())
	{
		// mDrawがtrueの時
		if (mDraw)
		{
			// 新しい画像を出す
			mNowDescription = new Sprite(mDescription[mNum]);
			// 一度newしたら、mDrawをfalseにする。
			mDraw = false;

			++mNum;

			// デストラクタで削除するようにvectorに保存しておく
			mDeleteDescription.push_back(mNowDescription);
		}
	}
	// 保存した分表示し終わったら
	if (mEndFlag)
	{
		mBackDescription->NotVisible();

		// 消さなきゃいけない画像があれば
		if (mDeleteDescription.size() != 0)
		{
			for (unsigned int i = 0; i < mDeleteDescription.size(); i++)
			{
				// 表示した画像を全て透明にする
				mDeleteDescription[i]->NotVisible();
			}
		}

		//　終わりの画像を表示してなければ
		if (mSprite == nullptr)
		{
			mSprite = new Sprite(mEndSprite);
		}
	}

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
}