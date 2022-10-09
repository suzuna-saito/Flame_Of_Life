#include "pch.h"

LastResult::LastResult(const SceneType& _nowScene)
	:ResultBase(_nowScene)
{
	if (mClearEndFlag)
	{
		mFullPicture = new FullPicture("Assets/UI/EndResult/Clear_1.png");
	}
	else
	{
		mFullPicture = new FullPicture("Assets/UI/EndResult/Clear_4.png");
	}
}

LastResult::~LastResult()
{
	// ���݂̃V�[���Ő��������I�u�W�F�N�g��S�č폜
	GAME_OBJECT_MANAGER->RemoveGameObjects(SceneType::eLastResult);
}

void LastResult::Input(const InputState& _state)
{
	// �R���g���[���[��A�{�^���A�܂��́A�X�y�[�X�L�[�������ꂽ�u��
	if (_state.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == ButtonState::Released ||
		_state.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::Released)
	{
		// �i�[����Ă���摜��`��
		// �S�ĕ`�悳��Ă������̓V�[���J�ڃt���O��true�ɂȂ�
		mGameSceneFlag = mDrawUpdate();
	}
	// �^�C�g���V�[���ȊO�ŃR���g���[���[�̃X�^�[�g�{�^���A�܂��́AB�L�[�������ꂽ�u��
	if (_state.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_START) == 1 ||
		_state.m_keyboard.GetKeyState(SDL_SCANCODE_B) == ButtonState::Released)
	{
		// �^�C�g���J�ڃt���O��true�ɂ���
		mReturnTitleFlag = true;
	}
}

SceneBase::SceneType LastResult::update()
{
	// mGameSceneFlag��true��������
	if (mGameSceneFlag)
	{
		// ���̃V�[���̃^�C�v��Ԃ�
		return SceneType::eTitle;
	}

	return mIsSceneType;
}