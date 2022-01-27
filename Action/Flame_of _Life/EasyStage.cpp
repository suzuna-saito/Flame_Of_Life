/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_nowScene ���݂̃V�[��
*/
EasyStage::EasyStage(const Scene& _nowScene)
	:SceneBase()
{
	SetScene(_nowScene);

	mMapCreate = new MapCreate();

	if (!mMapCreate->OpenFile())
	{
		// �w�i�̐���
		mMapCreate->CreateBackGround();
		// �v���C���[�̐���
		mMapCreate->CreatePlayer();
		// ���̐���
		mMapCreate->CreateGround();
		// �X�C�b�`�̐���
		mMapCreate->CreateSwitch();
		// �낤�����̐���
		mMapCreate->CreateCandle();
		// �A�C�e���̐���
		mMapCreate->CreateItem();
	}

	// �J�E���g�A�b�v
	new CountUp(_nowScene);
}

/*
@fn	�f�X�g���N�^
*/
EasyStage::~EasyStage()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(Scene::easy);

	delete mMapCreate;
}


void EasyStage::Input(const InputState& _state)
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
SceneBase* EasyStage::update()
{
	if (Candle::mCandleCount == 2)
	{
		return new NormalStage(Scene::normal);
		//return new Result(Scene::result);
	}

	CountUp::SetCountStartFlag(true);

	return this;
}
