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
	, mFirstFlag(true)
	, mDraw(true)
	, mBackDraw(false)
	, mCount(0)
	, mNum(0)
	, mNowDescription(nullptr)
{
	SetScene(_nowScene);

	// タイトル画像
	mSprite = new Sprite("Assets/UI/Result.png");

	// マップをつかってアイテムと説明画像を関連付け	
	mItemDescription[itemNames::cat] = "Assets/UI/Cat.png";
	mItemDescription[itemNames::chair] = "Assets/UI/Chair.png";
	mItemDescription[itemNames::chara] = "Assets/UI/Chara.png";
	mItemDescription[itemNames::lighter] = "Assets/UI/Lighter.png";
	mItemDescription[itemNames::sword] = "Assets/UI/Sword.png";
	mItemDescription[itemNames::tree] = "Assets/UI/Tree.png";
}

/*
@fn	デストラクタ
*/
Result::~Result()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(Scene::title);
	delete mSprite;
}

void Result::Input(const InputState& _state)
{
	if (_state.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_START) == 1 ||
		_state.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::Released)
	{
		mGameSceneFlag = true;
	}
}

/*
@fn	現在のシーン時に毎フレーム更新処理をする
*/
SceneBase* Result::update()
{
	// 一回だけ通る処理
	if (mFirstFlag)
	{
		// イテレーター
		decltype(mItemDescription)::iterator it;

		// 取得したアイテム分回す
		for (const auto& num : ItemBase::GetItemNames())
		{
			// 探す
			it = mItemDescription.find(num);

			// 見つかった
			if (it != mItemDescription.end())
			{
				// mDescriptionに見つかった分だけ保存
				mDescription.push_back(mItemDescription[num]);
				mBackDraw = true;
			}
		}

		if (mBackDraw)
		{
			mBackDescription = new Sprite("Assets/UI/ItemBack.png");
		}

		mFirstFlag = false;
	}
	
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
		}
		
		// カウントを足す
		++mCount;

		// カウントが100になったら
		if (mCount == 180)
		{
			// 今表示している説明文を消す
			mNowDescription->NotVisible();
		}
		if (mCount >= 200)
		{
			++mNum;

			mDraw = true;
			mCount = 0;
		}
	}
	// 保存した分表示し終わったら
	else
	{
		mBackDescription->NotVisible();

		mSprite = new Sprite("Assets/UI/End.png");
	}
	
	
	if (mGameSceneFlag)
	{
		return new Title(Scene::title);
	}

	return this;
}