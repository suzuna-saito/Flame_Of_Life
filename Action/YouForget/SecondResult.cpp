/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_nowScene ���݂̃V�[��
*/
SecondResult::SecondResult(const SceneType& _nowScene)
	:ResultBase(_nowScene)
{
	mFullPicture = new FullPicture("Assets/UI/SecondResult/SecondResultBase.png");

	// �}�b�v�������ăA�C�e���Ɛ����摜���֘A�t��	
	mPuzzlePieceDatas[ItemNum::one] = "Assets/UI/SecondResult/Puzzles_1.png";
	mPuzzlePieceDatas[ItemNum::two] = "Assets/UI/SecondResult/Puzzles_2.png";
	mPuzzlePieceDatas[ItemNum::three] = "Assets/UI/SecondResult/Puzzles_3.png";

	// �ǂ̃A�C�e��������Ă��邩����
	Search();
}

/*
@fn	�f�X�g���N�^
*/
SecondResult::~SecondResult()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(SceneType::eSecondResult);
}

void SecondResult::Input(const InputState& _state)
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
SceneBase* SecondResult::update()
{
	if (mGameSceneFlag)
	{
		return new ThirdStage(SceneType::eThird);
	}

	if (mReturnTitleFlag)
	{
		return new Title(SceneType::eTitle);
	}

	return this;
}