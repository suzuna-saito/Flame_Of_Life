/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_nowScene ���݂̃V�[��
*/
NormalStage::NormalStage(const Scene& _nowScene)
	:SceneBase()
{
	SetScene(_nowScene);

	mMapCreate = new MapCreate();

	if (!mMapCreate->OpenFile())
	{
		// ���̐���
		mMapCreate->CreateGround();
		// �X�C�b�`�𐶐�
		mMapCreate->CreateSwitch();
		// �v���C���[�̐���
		mMapCreate->CreatePlayer();
		// �낤�����̐���
		mMapCreate->CreateCandle();
		// �A�C�e���𐶐�
		mMapCreate->CreateItem();
	}

	// �J�E���g�A�b�v
	new CountUp(_nowScene);
}

/*
@fn	�f�X�g���N�^
*/
NormalStage::~NormalStage()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(Scene::normal);

	delete mMapCreate;
}


void NormalStage::Input(const InputState& _state)
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
SceneBase* NormalStage::update()
{
	if (Candle::mCandleCount == 3)
	{
		//return new HardStage(Scene::hard);
	}

	CountUp::SetCountStartFlag(true);

	return this;
}
