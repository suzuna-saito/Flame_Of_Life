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
		// ���̐���
		mMapCreate->CreateGround();
		// �v���C���[�̐���
		mMapCreate->CreatePlayer();
		// �낤�����̐���
		mMapCreate->CreateCandle();
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
	if (_state.m_keyboard.GetKeyState(SDL_SCANCODE_0) == 1)
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
		//return new EasyStage(easy);
	}

	CountUp::SetCountStartFlag(true);

	return this;
}
