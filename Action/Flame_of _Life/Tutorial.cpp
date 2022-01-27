/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_nowScene ���݂̃V�[��
*/
Tutorial::Tutorial(const Scene& _nowScene)
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
	}

	// �J�E���g�A�b�v
	new CountUp(_nowScene);
}

/*
@fn	�f�X�g���N�^
*/
Tutorial::~Tutorial()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(Scene::tutorial);

	delete mMapCreate;
}

void Tutorial::Input(const InputState& _state)
{
	// �����蔻��\�����[�h�̐؂�ւ�
	if (_state.m_keyboard.GetKeyState(SDL_SCANCODE_0) == ButtonState::Pressed)
	{
		PHYSICS->ToggleDebugMode();
	}
}

/*
@fn	���݂̃V�[�����ɖ��t���[���X�V����������
*/
SceneBase* Tutorial::update()
{
	// �v���C���[���낤�����ɂ��ǂ蒅������
	if (Candle::mCandleCount == 1)
	{
		// �J�ڃt���O��true�ɂ���
		mGameSceneFlag = true;
	}

	// �J�ڃt���O��true��������
	if (mGameSceneFlag)
	{
		return new EasyStage(Scene::easy);
	}

	CountUp::SetCountStartFlag(true);

	return this;
}