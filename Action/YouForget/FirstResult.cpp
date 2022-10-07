/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_nowScene ���݂̃V�[��
*/
FirstResult::FirstResult(const SceneType& _nowScene)
	:ResultBase()
{
	mFullPicture = new FullPicture("Assets/UI/FirstResult/FirstResultBase.png");

	// �}�b�v�������ăA�C�e���Ɛ����摜���֘A�t��	
	mPuzzles[ItemNum::one] = "Assets/UI/FirstResult/Puzzles_1.png";
	mPuzzles[ItemNum::two] = "Assets/UI/FirstResult/Puzzles_2.png";
	mPuzzles[ItemNum::three] = "Assets/UI/FirstResult/Puzzles_3.png";

	// �ǂ̃A�C�e��������Ă��邩����
	mSearch();
}

/*
@fn	�f�X�g���N�^
*/
FirstResult::~FirstResult()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(SceneType::eFirstResult);
}

void FirstResult::Input(const InputState& _state)
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
SceneBase* FirstResult::update()
{
	if (mGameSceneFlag)
	{
		return new SecondStage(SceneType::eSecond);

		//return new Result(Scene::gameClear);
	}

	if (mReturnTitleFlag)
	{
		return new Title(SceneType::eTitle);
	}

	mResultUpdate();

	return this;
}