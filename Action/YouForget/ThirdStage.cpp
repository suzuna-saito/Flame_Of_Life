#include "pch.h"

ThirdStage::ThirdStage(const SceneType& _nowScene)
	:SceneBase(_nowScene)
{
	// �}�b�v�̐���
	mMapCreate = new MapCreate(_nowScene);
	// ThirdStage�p�̃t�@�C�����J������
	if (!mMapCreate->OpenFile())
	{
		// �v���C���[�̐���
		mMapCreate->CreatePlayer();
		// �w�i�̐���
		mMapCreate->CreateBackGround();
		// ���̐���
		mMapCreate->CreateGround();
		// �X�C�b�`�̐���
		mMapCreate->CreateSwitch();
		// �낤�����̐���
		mMapCreate->CreateCandle();
		// �A�C�e���̐���
		mMapCreate->CreateItem();
	}
}

ThirdStage::~ThirdStage()
{
	// ���݂̃V�[���Ő��������I�u�W�F�N�g��S�č폜
	GAME_OBJECT_MANAGER->RemoveGameObjects(SceneType::eThird);
}


void ThirdStage::Input(const InputState& _state)
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

SceneBase::SceneType ThirdStage::update()
{
	// �v���C���[���S�[���ɂ��ǂ蒅������
	if (GoalObj::mGoalFlag)
	{
		// ���̃V�[���̃^�C�v��Ԃ�
		return SceneType::eThirdResult;
	}

	// mReturnTitleFlag��true��������
	if (mReturnTitleFlag)
	{
		// �^�C�g���V�[���^�C�v��Ԃ�
		return SceneType::eTitle;
	}

	return mIsSceneType;
}