#include "pch.h"

FirstResult::FirstResult(const SceneType& _nowScene)
	:ResultBase(_nowScene)
{
	// �p�Y���̓y��UI�𐶐�
	new PuzzleUI("Assets/UI/FirstResult/FirstResultBase.png", UIBase::UIType::ePuzzleBase);

	// �A�C�e���Ɖ摜�f�[�^���֘A�t��	
	mPuzzlePieceDatas[Item::PieceNum::one] = "Assets/UI/FirstResult/Puzzles_1.png";
	mPuzzlePieceDatas[Item::PieceNum::two] = "Assets/UI/FirstResult/Puzzles_2.png";
	mPuzzlePieceDatas[Item::PieceNum::three] = "Assets/UI/FirstResult/Puzzles_3.png";

	// �ǂ̃p�Y���s�[�X���擾�����������A�i�[
	Search();
	// �S�Ẵp�Y���s�[�X������o���Ă���
	if (Collected())
	{
		// ����o�����p�̃e�L�X�g�摜��ǉ��i�[
		StoresData("Assets/UI/FirstResult/Word_1.png", UIBase::UIType::eText);
		StoresData("Assets/UI/FirstResult/Word_2.png", UIBase::UIType::eText);
	}
}

FirstResult::~FirstResult()
{
	// ���݂̃V�[���Ő��������I�u�W�F�N�g��S�č폜
	GAME_OBJECT_MANAGER->RemoveGameObjects(SceneType::eFirstResult);
}

void FirstResult::Input(const InputState& _state)
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

SceneBase::SceneType FirstResult::update()
{
	// mGameSceneFlag��true��������
	if (mGameSceneFlag)
	{
		// ���̃V�[���̃^�C�v��Ԃ�
		return SceneType::eSecond;
		//return new SecondResult(SceneType::eSecondResult);

		//return new Result(Scene::gameClear);
	}

	// mReturnTitleFlag��true��������
	if (mReturnTitleFlag)
	{
		// �^�C�g���V�[���^�C�v��Ԃ�
		return SceneType::eTitle;
	}

	return mIsSceneType;
}