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
	, mDeleteDescription()
	, mNextFlag(false)
	, mEndFlag(false)
	, mDraw(false)
	, mNum(0)
	, mNowDescription(nullptr)
{
	SetScene(_nowScene);

	// �}�b�v�������ăA�C�e���Ɛ����摜���֘A�t��	
	mItemDescription[itemNames::cat] = "Assets/UI/FarstThree.png";
	mItemDescription[itemNames::chair] = "Assets/UI/FarstTwo.png";
	mItemDescription[itemNames::chara] = "Assets/UI/FarstOne.png";
	/*mItemDescription[itemNames::lighter] = "Assets/UI/Lighter.png";
	mItemDescription[itemNames::sword] = "Assets/UI/Sword.png";
	mItemDescription[itemNames::tree] = "Assets/UI/Tree.png";*/

	// �ǂ̃A�C�e��������Ă��邩����
	mSearch();

	// �������̌��ɏo���������ȉ摜
	mBackDescription = new Sprite("Assets/UI/BackPicture.png");
}

/*
@fn	�f�X�g���N�^
*/
Result::~Result()
{
	// �擾�����A�C�e���̒��Ƀf�[�^�������Ă����
	if (ItemBase::mGetNames.size() != 0)
	{
		ItemBase::mGetNames.clear();
	}

	// ���������f�[�^�������Ă�����
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
		// �Ō�̐����܂Ō����Ă���
		if (mEndFlag)
		{
			// �V�[���J�ڃt���O��true�ɂ���
			mGameSceneFlag = true;
		}

		// �Ō�̐����܂ŕ`��ł��ĂȂ�������
		if (mNum < mDescription.size())
		{
			// ���̐������o���悤�ɂ���
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
	// �C�e���[�^�[
	decltype(mItemDescription)::iterator it;

	// �擾�����A�C�e������
	for (const auto& num : ItemBase::mGetNames)
	{
		// �T��
		it = mItemDescription.find(num);

		// ��������
		if (it != mItemDescription.end())
		{
			// mDescription�Ɍ��������������ۑ�
			mDescription.push_back(mItemDescription[num]);
		}
	}
}

/*
@fn	���݂̃V�[�����ɖ��t���[���X�V����������
*/
SceneBase* Result::update()
{
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

			++mNum;

			// �f�X�g���N�^�ō폜����悤��vector�ɕۑ����Ă���
			mDeleteDescription.push_back(mNowDescription);
		}

	
	}
	// �ۑ��������\�����I�������
	if (mEndFlag)
	{
		// �����Ȃ��Ⴂ���Ȃ��摜�������
		if (mDeleteDescription.size() != 0)
		{
			for (unsigned int i = 0; i < mDeleteDescription.size(); i++)
			{
				// �\�������摜��S�ē����ɂ���
				mDeleteDescription[i]->NotVisible();
			}
		}

		mBackDescription->NotVisible();

		//�@�I���̉摜��\�����ĂȂ����
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