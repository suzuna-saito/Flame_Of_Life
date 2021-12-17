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
	, mFirstFlag(true)
	, mDraw(true)
	, mCount(0)
	, mNum(0)
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
	if (mFirstFlag)
	{
		for (const auto& num : ItemBase::GetItemNames())
		{
			// 探す
			it = mItemDescription.find(num);

			// 見つかった
			if (it != mItemDescription.end())
			{
				// 保存
				mDescription.push_back(mItemDescription[num]);
			}
		}

		mFirstFlag = false;
	}
	
	if (mNum < mDescription.size())
	{
		if (mDraw)
		{
			mSprite = new Sprite(mDescription[mNum]);
			mDraw = false;
		}
		
		++mCount;

		if (mCount >= 100)
		{
			++mNum;

			mDraw = true;
			mCount = 0;

			// 今表示している説明文を消す
			mSprite->NotVisible();
		}
	}
	else
	{
		mSprite = new Sprite("Assets/UI/End.png");
	}
	
	
	if (mGameSceneFlag)
	{
		return new Title(Scene::title);
	}

	return this;
}