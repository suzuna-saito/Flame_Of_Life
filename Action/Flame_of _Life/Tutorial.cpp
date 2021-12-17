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
		// �J�E���g�����炷
		mNextSceneCount--;
		// �J�E���g��0�ȉ��ɂȂ�����
		if (mNextSceneCount <= 0)
		{
			return new HardStage(Scene::hard);
		}
	}

	CountUp::SetCountStartFlag(true);

	return this;
}