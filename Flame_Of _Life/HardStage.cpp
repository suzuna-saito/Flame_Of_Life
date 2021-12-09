/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_nowScene ���݂̃V�[��
*/
HardStage::HardStage(const Scene& _nowScene)
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

	new ItemCount(_nowScene);
}

/*
@fn	�f�X�g���N�^
*/
HardStage::~HardStage()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(hard);

	delete mMapCreate;
}


void HardStage::Input(const InputState& _state)
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
SceneBase* HardStage::update()
{

	CountUp::SetCountStartFlag(true);

	return this;
}
