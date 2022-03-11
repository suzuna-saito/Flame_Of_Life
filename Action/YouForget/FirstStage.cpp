/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_nowScene ���݂̃V�[��
*/
FirstStage::FirstStage(const Scene& _nowScene)
	:SceneBase()
{
	SetScene(_nowScene);

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

	mSprite = new Sprite("Assets/UI/Description.png");
}

/*
@fn	�f�X�g���N�^
*/
FirstStage::~FirstStage()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(Scene::first);

	delete mSprite;
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
	if (Candle::mCandleCount == 1)
	{
		//return new SecondStage(Scene::second);
		return new FirstResult(Scene::firstResult);
	}

	if (mReturnTitleFlag)
	{
		return new Title(Scene::title);
	}


	// @@@
	if (!Player::mMoveFlag)
	{
		mSprite->SetThisVisible(true);
	}
	else
	{
		mSprite->SetThisVisible(false);
	}

	return this;
}
