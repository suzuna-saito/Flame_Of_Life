/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_nowScene ���݂̃V�[��
*/
SecondStage::SecondStage(const SceneType& _nowScene)
	:SceneBase()
{
	mIsScene = _nowScene;

	mMapCreate = new MapCreate();

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

	mFullPicture = new FullPicture("Assets/UI/Description.png");
}

/*
@fn	�f�X�g���N�^
*/
SecondStage::~SecondStage()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(SceneType::eSecond);

	delete mMapCreate;
	delete mFullPicture;
}


void SecondStage::Input(const InputState& _state)
{
	// �����蔻��\�����[�h�̐؂�ւ�
	if (_state.m_keyboard.GetKeyState(SDL_SCANCODE_0) == ButtonState::Pressed)
	{
		PHYSICS->ToggleDebugMode();
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
SceneBase* SecondStage::update()
{
	if (GoalObj::mGoalFlag)
	{
		return new SecondResult(SceneType::eSecondResult);
	}

	if (mReturnTitleFlag)
	{
		return new Title(SceneType::eTitle);
	}


	// @@@
	if (!Player::mMoveFlag)
	{
		mFullPicture->SetThisVisible(true);
	}
	else
	{
		mFullPicture->SetThisVisible(false);
	}
	return this;
}
