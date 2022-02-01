/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_nowScene 現在のシーン
*/
Result::Result(const Scene& _nowScene)
	:SceneBase()
	, mDescription()
	, mDeleteDescription()
	, mNextFlag(false)
	, mEndFlag(false)
	, mDraw(false)
	, mNum(0)
	, mNowDescription(nullptr)
{
	SetScene(_nowScene);

	// マップをつかってアイテムと説明画像を関連付け	
	mItemDescription[itemNames::cat] = "Assets/UI/FarstThree.png";
	mItemDescription[itemNames::chair] = "Assets/UI/FarstTwo.png";
	mItemDescription[itemNames::chara] = "Assets/UI/FarstOne.png";
	/*mItemDescription[itemNames::lighter] = "Assets/UI/Lighter.png";
	mItemDescription[itemNames::sword] = "Assets/UI/Sword.png";
	mItemDescription[itemNames::tree] = "Assets/UI/Tree.png";*/

	// どのアイテムを取っているか検索
	mSearch();

	// 説明文の後ろに出す薄透明な画像
	mBackDescription = new Sprite("Assets/UI/BackPicture.png");
}

/*
@fn	デストラクタ
*/
Result::~Result()
{
	// 取得したアイテムの中にデータが入っていれば
	if (ItemBase::mGetNames.size() != 0)
	{
		ItemBase::mGetNames.clear();
	}

	// 消したいデータが入っていたら
	int size = mDeleteDescription.size();
	for (int i = 0; i < size; i++)
	{
		delete mDeleteDescription[i];
	}

	delete mSprite;
	delete mBackDescription;
	GAME_OBJECT_MANAGER->RemoveGameObjects(Scene::result);
}

void Result::Input(const InputState& _state)
{
	if (_state.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == ButtonState::Released ||
		_state.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::Released)
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
}

void Result::mSearch()
{
	// イテレーター
	decltype(mItemDescription)::iterator it;

	// 取得したアイテム分回す
	for (const auto& num : ItemBase::mGetNames)
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

/*
@fn	現在のシーン時に毎フレーム更新処理をする
*/
SceneBase* Result::update()
{
	// 保存した分回す
	if (mNum < mDescription.size())
	{
		// mDrawがtrueの時
		if (mDraw)
		{
			// 新しい説明文を出す
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
		// 消さなきゃいけない画像があれば
		if (mDeleteDescription.size() != 0)
		{
			for (unsigned int i = 0; i < mDeleteDescription.size(); i++)
			{
				// 表示した画像を全て透明にする
				mDeleteDescription[i]->NotVisible();
			}
		}

		mBackDescription->NotVisible();

		//　終わりの画像を表示してなければ
		if (mSprite == nullptr)
		{
			mSprite = new Sprite("Assets/UI/End.png");
		}
	}


	if (mGameSceneFlag)
	{
		return new Title(Scene::title);
	}

	return this;
}