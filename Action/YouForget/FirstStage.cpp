#include "pch.h"

FirstStage::FirstStage(const SceneType& _nowScene)
	:SceneBase(_nowScene)
{
	// �}�b�v�̐���
	mMapCreate = new MapCreate(_nowScene);
	// ThirdStage�p�̃t�@�C�����J������
	if (!mMapCreate->OpenFile())
	{
		// �v���C���[�̐���
		mMapCreate->CreatePlayer();
		// ���̐���
		mMapCreate->CreateGround();
	}
}

FirstStage::~FirstStage()
{
	// ���݂̃V�[���Ő��������I�u�W�F�N�g��S�č폜
	GAME_OBJECT_MANAGER->RemoveGameObjects(SceneType::eFirst);
}

void FirstStage::Input(const InputState& _state)
{
	// @@@�f�o�b�N�p
	// �����蔻��\�����[�h�̐؂�ւ�
	if (_state.m_keyboard.GetKeyState(SDL_SCANCODE_0) == ButtonState::Pressed)
	{
		PHYSICS->ToggleDebugMode();
	}
	// �^�C�g���V�[���ȊO�ŃR���g���[���[�̃X�^�[�g�{�^���A�܂��́AB�L�[�������ꂽ�u��
	if (_state.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_START) == 1 ||
		_state.m_keyboard.GetKeyState(SDL_SCANCODE_B) == ButtonState::Released)
	{
		// �^�C�g���J�ڃt���O��true�ɂ���
		mReturnTitleFlag = true;
	}
}

SceneBase::SceneType FirstStage::update()
{
	// mGameSceneFlag��true���A�t�F�[�h������Ȃ����
	if (mGameSceneFlag && !Fade::mFadeFlag)
	{
		// ���̃V�[���̃^�C�v��Ԃ�
		return SceneType::eFirstResult;
	}
	// mReturnTitleFlag��true��������
	if (mReturnTitleFlag)
	{
		// �^�C�g���V�[���^�C�v��Ԃ�
		return SceneType::eTitle;
	}

	// �v���C���[���S�[���ɂ��ǂ蒅�������A�t�F�[�h�̍X�V�����Ă��Ȃ�������
	if (!Fade::mFadeFlag)
	{
		// �V�[���J�ڃt���O��true�ɂ���
		mGameSceneFlag = true;
		// �����t�F�[�h�A�E�g��������
		//mFade->SetFade(Color::Black, Fade::FadeType::eOut);
	}

	return mIsSceneType;
}