/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_nowScene ���݂̃V�[��
*/
ThirdResult::ThirdResult(const SceneType& _nowScene)
	:ResultBase()
{
	mFullPicture = new FullPicture("Assets/UI/ThirdResult/ThirdResultBase.png");

	// �}�b�v�������ăA�C�e���Ɛ����摜���֘A�t��	
	mPuzzles[ItemNum::one] = "Assets/UI/ThirdResult/Puzzles_1.png";
	mPuzzles[ItemNum::two] = "Assets/UI/ThirdResult/Puzzles_2.png";
	mPuzzles[ItemNum::three] = "Assets/UI/ThirdResult/Puzzles_3.png";

	// �ǂ̃A�C�e��������Ă��邩����
	mSearch();
}

/*
@fn	�f�X�g���N�^
*/
ThirdResult::~ThirdResult()
{
	delete mFullPicture;
	GAME_OBJECT_MANAGER->RemoveGameObjects(SceneType::eThirdResult);
}

void ThirdResult::Input(const InputState& _state)
{
	if (_state.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == ButtonState::Released ||
		_state.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::Released)
	{
		mDrawUpdate();
	}

	if (_state.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_START) == 1 ||
		_state.m_keyboard.GetKeyState(SDL_SCANCODE_B) == ButtonState::Released)
	{
		mReturnTitleFlag = true;
	}
}


/*
@fn	���݂̃V�[�����ɖ��t���[���X�V����������
*/
SceneBase* ThirdResult::update()
{
	mResultUpdate();

	if (mGameSceneFlag)
	{
		return new LastResult(SceneType::eGameClear);
	}

	if (mReturnTitleFlag)
	{
		return new Title(SceneType::eTitle);
	}

	return this;
}