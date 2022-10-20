#include "pch.h"

Game::Game()
	: mNowScene(nullptr)
	, mFps(nullptr)
	, mReturnSceneType(SceneBase::SceneType::eInit)
	, mRunningFlag(true)
	, mInputSystem(0)
	, MWidth(1920.0f)
	, MHeight(1080.0f)
{
}

bool Game::Initialize()
{
	// SDL�̏�����
	// �Ԃ�l�̐�����0�łȂ�������
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO |
		SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC) != 0)
	{
		printf("SDL���������ł��܂��� : %s", SDL_GetError());
		return false;
	}

	//���͊Ǘ��N���X�̏�����
	mInputSystem = new InputSystem();
	if (!mInputSystem->Initialize())
	{
		printf("�C���v�b�g�V�X�e���̏������Ɏ��s���܂���");
		return false;
	}

	//�����_���[�̏�����
	Renderer::CreateInstance();
	//��ʍ쐬
	if (!RENDERER->Initialize(MWidth, MHeight, false))
	{
		printf("�����_���[�̏������Ɏ��s���܂���\n");
		Renderer::DeleteInstance();
		return false;
	}

	//�����蔻��p�N���X�̏�����
	PhysicsWorld::CreateInstance();

	//FPS�Ǘ��N���X�̏�����
	mFps = new FPS();

	//�Q�[���I�u�W�F�N�g�Ǘ��N���X�̏�����
	GameObjectManager::CreateInstance();

	return true;
}

void Game::GameLoop()
{
	while (mRunningFlag)
	{
		// �t�F�[�h������Ȃ�������
		if (!Fade::mFadeFlag)
		{
			// ���͊֘A�̏���
			ProcessInput();
			// ���s���̃V�[���̓��͏���
			mNowScene->Input(mInputSystem->GetState());
		}
		// ���s���̃V�[�����X�V����
		mReturnSceneType = mNowScene->update();

		// �V�[���̐؂�ւ������������H
		if (SceneBase::mIsSceneType != mReturnSceneType)
		{
			// ���݂̃V�[���̉��
			delete mNowScene;
			// �V�[���̐؂�ւ�
			SetNewScene(mReturnSceneType);

			continue;
		}

		//�Q�[���̍X�V����
		UpdateGame();
		// ���݂̃V�[���̕`�揈��
		GenerateOutput();
		//FPS�̍X�V����
		mFps->Update();
	}
}

void Game::ProcessInput()
{
	// Update�̏���������
	mInputSystem->PrepareForUpdate();

	// �L���[�ɃC�x���g������ΌJ��Ԃ�
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:							// �T�u�V�X�e�����I��
			mRunningFlag = false;				// �Q�[�����[�v���I���
			break;
		//case SDL_MOUSEWHEEL:
		//	mInputSystem->ProcessEvent(event);
		//	break;
		default:
			break;
		}
	}

	// �t���[�����̏���
	mInputSystem->Update();

	// ���݂̏�Ԃ��i�[���ꂽ�z��
	const InputState& state = mInputSystem->GetState();

	// ESC�L�[���A�R���g���[���[�̏I���������ꂽ��
	if (state.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_BACK) ||
		state.m_keyboard.GetKeyState(SDL_SCANCODE_ESCAPE) == ButtonState::Released)
	{
		mRunningFlag = false;	// �Q�[�����[�v���I���
	}

	// �A�N�^�[�̓��͏�Ԃ̍X�V
	GAME_OBJECT_MANAGER->ProcessInput(state);
}

void Game::UpdateGame()
{
	// ���݂̃t���[���ɂ����������Ԃ��擾
	float deltaTime = mFps->GetDeltaTime();
	// �A�N�^�[�̍X�V����
	GAME_OBJECT_MANAGER->UpdateGameObject(deltaTime);
}

void Game::GenerateOutput()
{
	// ���s���̂��̂�`��
	RENDERER->Draw();
}

void Game::Termination()
{
	// �f�[�^�̃A�����[�h
	UnloadData();
	// �X�^�e�B�b�N�N���X�̉������
	GameObjectManager::DeleteInstance();	// Object
	Renderer::DeleteInstance();				// Renderer
	PhysicsWorld::DeleteInstance();			// PhysicsWorld
	// �N���X�̉������
	delete mFps;
	delete mInputSystem;
	// �T�u�V�X�e���̏I��
	SDL_Quit();
}

void Game::UnloadData()
{
	// �`�悵�Ă���f�[�^���폜
	if (RENDERER != nullptr)
	{
		RENDERER->UnloadData();	// ���
		RENDERER->Shutdown();	// �I������
	}
}

void Game::SetNewScene(const SceneBase::SceneType _sceneType)
{
	switch (_sceneType)
	{
	case SceneBase::SceneType::eTitle:			// Title
		mNowScene = new Title(_sceneType);
		break;
	case SceneBase::SceneType::eFirst:			// FirstStage
		mNowScene = new FirstStage(_sceneType);
		break;
	case SceneBase::SceneType::eSecond:			// SecondStage
		mNowScene = new SecondStage(_sceneType);
		break;
	case SceneBase::SceneType::eThird:			// ThirdStage
		mNowScene = new ThirdStage(_sceneType);
		break;
	case SceneBase::SceneType::eFirstResult:	// FirstResult
		mNowScene = new FirstResult(_sceneType);
		break;
	case SceneBase::SceneType::eSecondResult:	// SecondResult
		mNowScene = new SecondResult(_sceneType);
		break;
	case SceneBase::SceneType::eThirdResult:	// ThirdResult
		mNowScene = new ThirdResult(_sceneType);
		break;
	case SceneBase::SceneType::eLastResult:		// LastResult
		mNowScene = new LastResult(_sceneType);
		break;
	default:
		break;
	}
}