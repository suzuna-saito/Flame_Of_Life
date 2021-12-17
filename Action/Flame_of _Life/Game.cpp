/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn	�R���X�g���N�^
*/
Game::Game()
	: mFps(nullptr)
	, mRunningFlag(true)
	, mSceneFlag(false)
	, mInputSystem(0)
	, MWidth(1920.0f)
	, MHeight(1080.0f)
{
}

/*
@fn		����������
@return true : ���� , false : ���s(bool�^)
*/
bool Game::Initialize()
{
	//SDL�̏�����
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	//���͊Ǘ��N���X�̏�����
	mInputSystem = new InputSystem();
	if (!mInputSystem->Initialize())
	{
		SDL_Log("Failed to initialize input system");
		return false;
	}

	//�����_���[�̏�����
	Renderer::CreateInstance();
	//��ʍ쐬
	if (!RENDERER->Initialize(MWidth, MHeight, false))
	{
		SDL_Log("Failed to initialize renderer");
		Renderer::DeleteInstance();
		return false;
	}

	//�����蔻��p�N���X�̏�����
	PhysicsWorld::CreateInstance();

	//FPS�Ǘ��N���X�̏�����
	mFps = new FPS();

	//�Q�[���I�u�W�F�N�g�Ǘ��N���X�̏�����
	GameObjectManager::CreateInstance();

	Matrix4 v = Matrix4::CreateLookAt(Vector3(200, 0, -500), Vector3(200, 0, 0), Vector3::UnitZ);
	RENDERER->SetViewMatrix(v);

	return true;
}

/*
@fn	�I������
*/
void Game::Termination()
{
	//�f�[�^�̃A�����[�h
	UnloadData();
	//�X�^�e�B�b�N�N���X�̉������
	GameObjectManager::DeleteInstance();
	Renderer::DeleteInstance();
	PhysicsWorld::DeleteInstance();
	//�N���X�̉������
	delete mFps;
	delete mInputSystem;
	//�T�u�V�X�e���̏I��
	SDL_Quit();
}

/*
@fn		�ŏ��̃V�[�������߂�֐�
@param	_firstScene �ŏ��̃V�[��
*/
void Game::SetFirstScene(SceneBase* _firstScene)
{
	mNowScene = _firstScene;
}

/*
@fn	�Q�[�����[�v
*/
void Game::GameLoop()
{
	while (mRunningFlag)
	{
		//���͊֘A�̏���
		ProcessInput();

		SceneBase* tmpScene;
		//const InputState& state = mInputSystem->GetState();

		mNowScene->Input(mInputSystem->GetState());

		// ���s���̃V�[�����X�V����
		tmpScene = mNowScene->update();

		// �V�[���̐؂�ւ������������H
		if (tmpScene != mNowScene)
		{
			// ���݂̃V�[���̉��
			delete mNowScene;

			// ���ݎ��s���̃V�[���̐؂�ւ�
			mNowScene = tmpScene;
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

/*
@fn	���[�h�����f�[�^�̉��
*/
void Game::UnloadData()
{
	if (RENDERER != nullptr)
	{
		RENDERER->UnloadData();
		RENDERER->Shutdown();
	}
}

/*
@fn	���͊֘A�̏���
*/
void Game::ProcessInput()
{
	mInputSystem->PrepareForUpdate();

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mRunningFlag = false;
			break;
		case SDL_MOUSEWHEEL:
			mInputSystem->ProcessEvent(event);
			break;
		default:
			break;
		}
	}

	mInputSystem->Update();
	const InputState& state = mInputSystem->GetState();

	if (state.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_BACK) ||
		state.m_keyboard.GetKeyState(SDL_SCANCODE_ESCAPE) == ButtonState::Released)
	{
		mRunningFlag = false;
	}

	GAME_OBJECT_MANAGER->ProcessInput(state);
}

/*
@fn	�`��֘A�̏���
*/
void Game::GenerateOutput()
{
	RENDERER->Draw();
}

/*
@fn	�Q�[���̍X�V����
*/
void Game::UpdateGame()
{
	float deltaTime = mFps->GetDeltaTime();

	GAME_OBJECT_MANAGER->UpdateGameObject(deltaTime);
}