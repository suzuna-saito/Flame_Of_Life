/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_nowScene ���݂̃V�[��
*/
testResult::testResult(const Scene& _nowScene)
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
	mInit();

	// �������̌��ɏo���������ȉ摜
	mBackDescription = new Sprite("Assets/UI/BackPicture.png");
}

/*
@fn	�f�X�g���N�^
*/
testResult::~testResult()
{
	int size = mDeleteDescription.size();

	for (int i = 0; i < size; i++)
	{
		// �摜�������Ă�����
		if (mDeleteDescription[i] != nullptr)
		{
			delete mDeleteDescription[i];
		}
	}

	delete mSprite;
	delete mBackDescription;
	GAME_OBJECT_MANAGER->RemoveGameObjects(Scene::result);
}

void testResult::Input(const InputState& _state)
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
			//mNextFlag = true;

			mDraw = true;
		}
		else
		{
			mEndFlag = true;
		}
	}
}

void testResult::mInit()
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
SceneBase* testResult::update()
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

			// ��X�폜����悤��vector�ɕۑ����Ă���
			mDeleteDescription.push_back(mNowDescription);
		}

		// ���̐����̕`�������Ƃ�
		/*if (mNextFlag)
		{
			mNextFlag = false;
		}*/
	}
	// �ۑ��������\�����I�������
	if (mEndFlag)
	{
		// �����Ȃ��Ⴂ���Ȃ��摜�������
		if (mDeleteDescription[0] != nullptr)
		{
			for (int i = 0; i < mDeleteDescription.size(); i++)
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