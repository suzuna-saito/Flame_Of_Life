/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_nowScene ���݂̃V�[��
*/
Title::Title(const Scene& _nowScene)
	:SceneBase()
{
	SetScene(_nowScene);

	// �^�C�g���摜
	mSprite = new Sprite("Assets/UI/Title.png");

}

/*
@fn	�f�X�g���N�^
*/
Title::~Title()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(title);
	delete mSprite;
}

void Title::Input(const InputState& _state)
{
	if (_state.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_START) == 1 ||
		_state.m_keyboard.GetKeyValue(SDL_SCANCODE_SPACE) == 1)
	{
		mGameSceneFlag = true;
	}
}

/*
@fn	���݂̃V�[�����ɖ��t���[���X�V����������
*/
SceneBase* Title::update()
{

	if (mGameSceneFlag)
	{
		return new Tutorial(tutorial);
	}

	return this;
}