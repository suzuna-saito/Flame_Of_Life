/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_nowScene ���݂̃V�[��
*/
FirstStage::FirstStage(const SceneType& _nowScene)
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
FirstStage::~FirstStage()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(SceneType::eFirst);

	delete mFullPicture;
	delete mMapCreate;
}


void FirstStage::Input(const InputState& _state)
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
SceneBase* FirstStage::update()
{
	if (GoalObj::mGoalFlag)
	{
		//return new SecondStage(Scene::second);
		return new FirstResult(SceneType::eFirstResult);
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
