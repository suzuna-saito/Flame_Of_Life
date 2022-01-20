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
	, mNextFlag(false)
	, mEndFlag(false)
	, mDraw(true)
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

	// �ǂ̃A�C�e��������Ă��邩����
	mInit();

	// �������̌��ɏo���������ȉ摜
	mBackDescription = new Sprite("Assets/UI/ItemBack.png");
}

/*
@fn	�f�X�g���N�^
*/
Result::~Result()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(Scene::result);
	delete mSprite;
}

void Result::Input(const InputState& _state)
{
	if (_state.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_START) == 1 ||
		_state.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::Released)
	{
		// �Ō�̐����܂ŕ`��ł��ĂȂ�������
		if (!mEndFlag)
		{
			// ���̐������o���悤�ɂ���
			mNextFlag = true;
		}
		// �Ō�̐����܂Ō����Ă���
		else
		{
			// �V�[���J�ڃt���O��true�ɂ���
			mGameSceneFlag = true;
		}
	}
}

void Result::mInit()
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
		}
		
		// ���̐����̕`�������Ƃ�
		if (mNextFlag)
		{
			// ���\�����Ă��������������
			mNowDescription->NotVisible();

			++mNum;

			mDraw = true;
			mNextFlag = false;
		}
	}
	// �ۑ��������\�����I�������
	else
	{
		mBackDescription->NotVisible();

		mSprite = new Sprite("Assets/UI/End.png");

		mEndFlag = true;
	}
	
	
	if (mGameSceneFlag)
	{
		return new Title(Scene::title);
	}

	return this;
}