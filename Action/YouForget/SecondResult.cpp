#include "pch.h"

SecondResult::SecondResult(const SceneType& _nowScene)
	:ResultBase(_nowScene)
{
	// �p�Y���̓y��UI�𐶐�
	new PuzzleUI("Assets/UI/SecondResult/SecondResultBase.png", UIBase::UIType::ePuzzleBase);

	// �A�C�e���Ɖ摜�f�[�^���֘A�t��	
	mPuzzlePieceDatas[ItemNum::one] = "Assets/UI/SecondResult/Puzzles_1.png";
	mPuzzlePieceDatas[ItemNum::two] = "Assets/UI/SecondResult/Puzzles_2.png";
	mPuzzlePieceDatas[ItemNum::three] = "Assets/UI/SecondResult/Puzzles_3.png";

	// �ǂ̃p�Y���s�[�X���擾�����������A�i�[
	Search();
	// �S�Ẵp�Y���s�[�X������o���Ă���
	if (Collected())
	{
		// ����o�����p�̃e�L�X�g�摜��ǉ��i�[
		StoresData("Assets/UI/SecondResult/Word_1.png", UIBase::UIType::eText);
		StoresData("Assets/UI/SecondResult/Word_2.png", UIBase::UIType::eText);
	}
}

SecondResult::~SecondResult()
{
	// ���݂̃V�[���Ő��������I�u�W�F�N�g��S�č폜
	GAME_OBJECT_MANAGER->RemoveGameObjects(SceneType::eSecondResult);
}

void SecondResult::Input(const InputState& _state)
{
	// �R���g���[���[��A�{�^���A�܂��́A�X�y�[�X�L�[�������ꂽ�u��
	if (_state.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == ButtonState::Released ||
		_state.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::Released)
	{
		// �i�[����Ă���摜��`��
		// �S�ĕ`�悳��Ă������̓V�[���J�ڃt���O��true�ɂȂ�
		mGameSceneFlag = mDrawUpdate();
	}
}

SceneBase* SecondResult::update()
{
	// mGameSceneFlag��true��������
	if (mGameSceneFlag)
	{
		// ���̃V�[���̃|�C���^��Ԃ�
		return new ThirdStage(SceneType::eThird);
	}

	// mReturnTitleFlag��true��������
	if (mReturnTitleFlag)
	{
		// �^�C�g���V�[���̃|�C���^��Ԃ�
		return new Title(SceneType::eTitle);
	}

	return this;
}