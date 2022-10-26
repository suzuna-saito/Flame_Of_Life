/*
@brief	インクルード
*/
#include "pch.h"

//自身のインスタンスの初期化
GameObjectManager* GameObjectManager::mManager = nullptr;

/*
@fn インスタンスを生成
*/
void GameObjectManager::CreateInstance()
{
	if (mManager == nullptr)
	{
		mManager = new GameObjectManager();
		GameObject::CreateMainCamera();
	}
}

/*
@fn インスタンスを削除
*/
void GameObjectManager::DeleteInstance()
{
	if (mManager != nullptr)
	{
		delete mManager;
		mManager = nullptr;
	}
}

/*
@brief  ゲームオブジェクトのアップデート処理
*/
void GameObjectManager::UpdateGameObject(float _deltaTime)
{

	mUpdatingGameObject = true;

	// カメラを更新する
	for (auto cameraObject : mCameraObjects)
	{
		cameraObject->Update(_deltaTime);
	}

	// タイトルを更新する
	for (auto titleObject : mTitleObjects)
	{
		titleObject->Update(_deltaTime);
	}
	// チュートリアルを更新する
	for (auto tutorialObject : mTutorialObjects)
	{
		tutorialObject->Update(_deltaTime);
	}
	// Easyステージを更新する
	for (auto easystageObject : mEasyStageObjects)
	{
		easystageObject->Update(_deltaTime);
	}
	// Normaステージを更新する
	for (auto normalstageObject : mNormalStageObjects)
	{
		normalstageObject->Update(_deltaTime);
	}
	// Hardステージを更新する
	for (auto hardstageObject : mHardStageObjects)
	{
		hardstageObject->Update(_deltaTime);
	}
	// リザルトステージを更新する
	for (auto resultObject : mResultObjects)
	{
		resultObject->Update(_deltaTime);
	}

	mUpdatingGameObject = false;

	//待機中のオブジェクトを更新中オブジェクトに追加
	for (auto pending : mPendingGameObjects)
	{
		pending->ComputeWorldTransform();
		if (pending->GetScene() == SceneBase::SceneType::eTitle)
		{
			mTitleObjects.emplace_back(pending);
		}
		if (pending->GetScene() == SceneBase::SceneType::eTutorial)
		{
			mTutorialObjects.emplace_back(pending);
		}
		if (pending->GetScene() == SceneBase::SceneType::eFirst)
		{
			mEasyStageObjects.emplace_back(pending);
		}
		if (pending->GetScene() == SceneBase::SceneType::eSecond)
		{
			mNormalStageObjects.emplace_back(pending);
		}
		if (pending->GetScene() == SceneBase::SceneType::eThird)
		{
			mHardStageObjects.emplace_back(pending);
		}
	}
	mPendingGameObjects.clear();
}
/*
@brief  ゲームオブジェクトの入力処理
*/
void GameObjectManager::ProcessInput(const InputState& _state)
{
	mUpdatingGameObject = true;

	for (auto tutorialObject : mTutorialObjects)
	{
		tutorialObject->ProcessInput(_state);
	}

	for (auto easystageObject : mEasyStageObjects)
	{
		easystageObject->ProcessInput(_state);
	}

	for (auto normalstageObject : mNormalStageObjects)
	{
		normalstageObject->ProcessInput(_state);
	}

	for (auto hardstageObject : mHardStageObjects)
	{
		hardstageObject->ProcessInput(_state);
	}

	for (auto resultObject : mResultObjects)
	{
		resultObject->ProcessInput(_state);
	}

	mUpdatingGameObject = false;
}

/*
@brief  ゲームオブジェクトの追加
@param	追加するGameObjectクラスのポインタ
*/
void GameObjectManager::AddGameObject(GameObject* _object)
{
	if (mUpdatingGameObject)
	{
		mPendingGameObjects.emplace_back(_object);
	}
	else
	{
		switch (_object->GetTag())
		{
		case CollisionTag::eCamera:
			mCameraObjects.emplace_back(_object);
			break;
		}

		switch (_object->GetScene())
		{
		case SceneBase::SceneType::eTitle:
			mTitleObjects.emplace_back(_object);
			break;
		case SceneBase::SceneType::eTutorial:
			mTutorialObjects.emplace_back(_object);
			break;
		case SceneBase::SceneType::eFirst :
			mEasyStageObjects.emplace_back(_object);
			break;
		case SceneBase::SceneType::eSecond:
			mNormalStageObjects.emplace_back(_object);
			break;
		case SceneBase::SceneType::eThird:
			mHardStageObjects.emplace_back(_object);
			break;
		case SceneBase::SceneType::eFirstResult:
		case SceneBase::SceneType::eSecondResult:
		case SceneBase::SceneType::eThirdResult:
		case SceneBase::SceneType::eLastResult:

			mResultObjects.emplace_back(_object);
			break;
		}
	}
}

/*
@brief  ゲームオブジェクトの削除
@param	削除するGameObjectクラスのポインタ
*/
void GameObjectManager::RemoveGameObject(GameObject* _object)
{
	auto iter = std::find(mPendingGameObjects.begin(), mPendingGameObjects.end(), _object);
	if (iter != mPendingGameObjects.end())
	{
		std::iter_swap(iter, mPendingGameObjects.end() - 1);
		mPendingGameObjects.pop_back();
	}

	// タイトルシーン
	iter = std::find(mTitleObjects.begin(), mTitleObjects.end(), _object);
	if (iter != mTitleObjects.end())
	{
		std::iter_swap(iter, mTitleObjects.end() - 1);
		mTitleObjects.pop_back();
	}
	// チュートリアル
	iter = std::find(mTutorialObjects.begin(), mTutorialObjects.end(), _object);
	if (iter != mTutorialObjects.end())
	{
		std::iter_swap(iter, mTutorialObjects.end() - 1);
		mTutorialObjects.pop_back();
	}
	// Easyシーン
	iter = std::find(mEasyStageObjects.begin(), mEasyStageObjects.end(), _object);
	if (iter != mEasyStageObjects.end())
	{
		std::iter_swap(iter, mEasyStageObjects.end() - 1);
		mEasyStageObjects.pop_back();
	}
	// Normalシーン
	iter = std::find(mNormalStageObjects.begin(), mNormalStageObjects.end(), _object);
	if (iter != mNormalStageObjects.end())
	{
		std::iter_swap(iter, mNormalStageObjects.end() - 1);
		mNormalStageObjects.pop_back();
	}
	// Hardシーン
	iter = std::find(mHardStageObjects.begin(), mHardStageObjects.end(), _object);
	if (iter != mHardStageObjects.end())
	{
		std::iter_swap(iter, mHardStageObjects.end() - 1);
		mHardStageObjects.pop_back();
	}
	// リザルトシーン
	iter = std::find(mResultObjects.begin(), mResultObjects.end(), _object);
	if (iter != mResultObjects.end())
	{
		std::iter_swap(iter, mResultObjects.end() - 1);
		mResultObjects.pop_back();
	}

}

void GameObjectManager::RemoveGameObjects(SceneBase::SceneType _scene)
{
	switch (_scene)
	{
	case SceneBase::SceneType::eTitle:

		while (!mTitleObjects.empty())
		{
			delete mTitleObjects.back();
		}
		break;

	case SceneBase::SceneType::eTutorial:

		while (!mTutorialObjects.empty())
		{
			delete mTutorialObjects.back();
		}
		break;

	case SceneBase::SceneType::eFirst:

		while (!mEasyStageObjects.empty())
		{
			delete mEasyStageObjects.back();
		}
		break;

	case SceneBase::SceneType::eSecond:

		while (!mNormalStageObjects.empty())
		{
			delete mNormalStageObjects.back();
		}
		break;

	case SceneBase::SceneType::eThird:

		while (!mHardStageObjects.empty())
		{
			delete mHardStageObjects.back();
		}
		break;

	case SceneBase::SceneType::eFirstResult:
	case SceneBase::SceneType::eSecondResult:
	case SceneBase::SceneType::eThirdResult:
	case SceneBase::SceneType::eLastResult:

		while (!mResultObjects.empty())
		{
			delete mResultObjects.back();
		}
		break;
	}
}


GameObjectManager::GameObjectManager()
	: mUpdatingGameObject(false)
{
}


GameObjectManager::~GameObjectManager()
{
}