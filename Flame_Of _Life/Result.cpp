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
	, mFirstFlag(true)
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
	if (mFirstFlag)
	{
		for (int num = 0; num <= ItemBase::GetItemNames().size(); num++)
		{
			// �T���Ăق�����ł��BGetItemNames()�͏o���Ă��ł��B�ŁH
			it = mItemDescription.find(ItemBase::GetItemNames()[num]);

			// �����������āA��������ł�
			if (it != mItemDescription.end())
			{
				mSprite = new Sprite(mItemDescription[ItemBase::GetItemNames()[num]]);
			}
		}

		mFirstFlag = false;
	}
	
	
	if (mGameSceneFlag)
	{
		return new Title(Scene::title);
	}

	return this;
}