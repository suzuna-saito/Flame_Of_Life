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
		// ���̐���
		mMapCreate->CreateGround();
		// �v���C���[�̐���
		mMapCreate->CreatePlayer();
		// �낤�����̐���
		mMapCreate->CreateCandle();
	}

	//mCandle = nullptr;

	// �J�E���g�A�b�v
	new CountUp(_nowScene);
}

/*
@fn	�f�X�g���N�^
*/
Tutorial::~Tutorial()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(tutorial);

	delete mMapCreate;
}

void Tutorial::Input(const InputState& _state)
{
	// �����蔻��\�����[�h�̐؂�ւ�
	if (_state.m_keyboard.GetKeyState(SDL_SCANCODE_0) == 1)
	{
		PHYSICS->ToggleDebugMode();
	}
}

/*
@fn	���݂̃V�[�����ɖ��t���[���X�V����������
*/
SceneBase* Tutorial::update()
{
	if (Candle::mCandleCount == 1)
	{
		//return new NormalStage(normal);
		//return new EasyStage(easy);
		return new HardStage(hard);
	}

	CountUp::SetCountStartFlag(true);

	return this;
}