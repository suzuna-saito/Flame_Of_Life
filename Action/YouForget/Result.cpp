/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_nowScene ���݂̃V�[��
*/
Result::Result(const SceneType& _nowScene)
	:ResultBase(_nowScene)
{
	if (mTrueEndFlag)
	{
		mSprite = new Sprite("Assets/UI/EndResult/Clear_1.png");
	}
	else
	{
		mSprite = new Sprite("Assets/UI/EndResult/Clear_4.png");
	}

	mSearch();
}

/*
@fn	�f�X�g���N�^
*/
Result::~Result()
{
	delete mSprite;

	GAME_OBJECT_MANAGER->RemoveGameObjects(SceneType::eGameClear);
}

void Result::Input(const InputState& _state)
{
	if (_state.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == ButtonState::Released ||
		_state.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::Released)
	{
		mDrawUpdate();
	}
}


/*
@fn	���݂̃V�[�����ɖ��t���[���X�V����������
*/
SceneBase* Result::update()
{
	if (mGameSceneFlag)
	{
		return new Title(SceneType::eTitle);
	}

	mResultUpdate();

	return this;
}