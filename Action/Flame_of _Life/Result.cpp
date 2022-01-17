/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_nowScene ���݂̃V�[��
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

	// �^�C�g���摜
	mSprite = new Sprite("Assets/UI/Result.png");

	// �}�b�v�������ăA�C�e���Ɛ����摜���֘A�t��	
	mItemDescription[itemNames::cat] = "Assets/UI/Cat.png";
	mItemDescription[itemNames::chair] = "Assets/UI/Chair.png";
	mItemDescription[itemNames::chara] = "Assets/UI/Chara.png";
	mItemDescription[itemNames::lighter] = "Assets/UI/Lighter.png";
	mItemDescription[itemNames::sword] = "Assets/UI/Sword.png";
	mItemDescription[itemNames::tree] = "Assets/UI/Tree.png";
}

/*
@fn	�f�X�g���N�^
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
@fn	���݂̃V�[�����ɖ��t���[���X�V����������
*/
SceneBase* Result::update()
{
	// ��񂾂��ʂ鏈��
	if (mFirstFlag)
	{
		// �C�e���[�^�[
		decltype(mItemDescription)::iterator it;

		// �擾�����A�C�e������
		for (const auto& num : ItemBase::GetItemNames())
		{
			// �T��
			it = mItemDescription.find(num);

			// ��������
			if (it != mItemDescription.end())
			{
				// mDescription�Ɍ��������������ۑ�
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
	
	// �ۑ���������
	if (mNum < mDescription.size())
	{
		// mDraw��true�̎�
		if (mDraw)
		{
			// �V�������������o��
			mNowDescription = new Sprite(mDescription[mNum]);
			// ��xnew������AmDraw��false�ɂ���B
			mDraw = false;
		}
		
		// �J�E���g�𑫂�
		++mCount;

		// �J�E���g��100�ɂȂ�����
		if (mCount == 180)
		{
			// ���\�����Ă��������������
			mNowDescription->NotVisible();
		}
		if (mCount >= 200)
		{
			++mNum;

			mDraw = true;
			mCount = 0;
		}
	}
	// �ۑ��������\�����I�������
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