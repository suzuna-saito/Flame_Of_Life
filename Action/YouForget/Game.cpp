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
	// SDLの初期化
	// 返り値の整数が0でなかったら
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO |
		SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC) != 0)
	{
		printf("SDLを初期化できません : %s", SDL_GetError());
		return false;
	}

	//入力管理クラスの初期化
	mInputSystem = new InputSystem();
	if (!mInputSystem->Initialize())
	{
		printf("インプットシステムの初期化に失敗しました");
		return false;
	}

	//レンダラーの初期化
	Renderer::CreateInstance();
	//画面作成
	if (!RENDERER->Initialize(MWidth, MHeight, false))
	{
		printf("レンダラーの初期化に失敗しました\n");
		Renderer::DeleteInstance();
		return false;
	}

	//当たり判定用クラスの初期化
	PhysicsWorld::CreateInstance();

	//FPS管理クラスの初期化
	mFps = new FPS();

	//ゲームオブジェクト管理クラスの初期化
	GameObjectManager::CreateInstance();

	return true;
}

void Game::GameLoop()
{
	while (mRunningFlag)
	{
		// フェード中じゃなかったら
		if (!Fade::mFadeFlag)
		{
			// 入力関連の処理
			ProcessInput();
			// 実行中のシーンの入力処理
			mNowScene->Input(mInputSystem->GetState());
		}
		// 実行中のシーンを更新処理
		mReturnSceneType = mNowScene->update();

		// シーンの切り替えが発生した？
		if (SceneBase::mIsSceneType != mReturnSceneType)
		{
			// 現在のシーンの解放
			delete mNowScene;
			// シーンの切り替え
			SetNewScene(mReturnSceneType);

			continue;
		}

		//ゲームの更新処理
		UpdateGame();
		// 現在のシーンの描画処理
		GenerateOutput();
		//FPSの更新処理
		mFps->Update();
	}
}

void Game::ProcessInput()
{
	// Updateの準備をする
	mInputSystem->PrepareForUpdate();

	// キューにイベントがあれば繰り返す
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:							// サブシステムを終了
			mRunningFlag = false;				// ゲームループを終わる
			break;
		//case SDL_MOUSEWHEEL:
		//	mInputSystem->ProcessEvent(event);
		//	break;
		default:
			break;
		}
	}

	// フレーム毎の処理
	mInputSystem->Update();

	// 現在の状態が格納された配列
	const InputState& state = mInputSystem->GetState();

	// ESCキーか、コントローラーの終了が押されたら
	if (state.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_BACK) ||
		state.m_keyboard.GetKeyState(SDL_SCANCODE_ESCAPE) == ButtonState::Released)
	{
		mRunningFlag = false;	// ゲームループを終わる
	}

	// アクターの入力状態の更新
	GAME_OBJECT_MANAGER->ProcessInput(state);
}

void Game::UpdateGame()
{
	// 現在のフレームにかかった時間を取得
	float deltaTime = mFps->GetDeltaTime();
	// アクターの更新処理
	GAME_OBJECT_MANAGER->UpdateGameObject(deltaTime);
}

void Game::GenerateOutput()
{
	// 実行中のものを描画
	RENDERER->Draw();
}

void Game::Termination()
{
	// データのアンロード
	UnloadData();
	// スタティッククラスの解放処理
	GameObjectManager::DeleteInstance();	// Object
	Renderer::DeleteInstance();				// Renderer
	PhysicsWorld::DeleteInstance();			// PhysicsWorld
	// クラスの解放処理
	delete mFps;
	delete mInputSystem;
	// サブシステムの終了
	SDL_Quit();
}

void Game::UnloadData()
{
	// 描画しているデータを削除
	if (RENDERER != nullptr)
	{
		RENDERER->UnloadData();	// 解放
		RENDERER->Shutdown();	// 終了処理
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