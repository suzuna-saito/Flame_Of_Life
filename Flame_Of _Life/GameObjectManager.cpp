/*
@brief	�C���N���[�h
*/
#include "pch.h"

//���g�̃C���X�^���X�̏�����
GameObjectManager* GameObjectManager::mManager = nullptr;

/*
@fn �C���X�^���X�𐶐�
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
@fn �C���X�^���X���폜
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
@brief  �Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g����
*/
void GameObjectManager::UpdateGameObject(float _deltaTime)
{

	mUpdatingGameObject = true;

	// �J�������X�V����
	for (auto cameraObject : mCameraObjects)
	{
		cameraObject->Update(_deltaTime);
	}

	// �`���[�g���A�����X�V����
	for (auto tutorialObject : mTutorialObjects)
	{
		tutorialObject->Update(_deltaTime);
	}

	// �X�e�[�W�P���X�V����
	for (auto stage01Object : mStage01Objects)
	{
		stage01Object->Update(_deltaTime);
	}

	mUpdatingGameObject = false;

	//�ҋ@���̃I�u�W�F�N�g���X�V���I�u�W�F�N�g�ɒǉ�
	for (auto pending : mPendingGameObjects)
	{
		pending->ComputeWorldTransform();
		if (pending->GetScene() == SceneBase::Scene::tutorial)
		{
			mTutorialObjects.emplace_back(pending);
		}
		if (pending->GetScene() == SceneBase::Scene::easy)
		{
			mStage01Objects.emplace_back(pending);
		}
	}
	mPendingGameObjects.clear();
}
/*
@brief  �Q�[���I�u�W�F�N�g�̓��͏���
*/
void GameObjectManager::ProcessInput(const InputState& _state)
{
	mUpdatingGameObject = true;

	for (auto tutorialObject : mTutorialObjects)
	{
		tutorialObject->ProcessInput(_state);
	}

	for (auto stage01Object : mStage01Objects)
	{
		stage01Object->ProcessInput(_state);
	}

	mUpdatingGameObject = false;
}

/*
@brief  �Q�[���I�u�W�F�N�g�̒ǉ�
@param	�ǉ�����GameObject�N���X�̃|�C���^
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
		case Camera:
			mCameraObjects.emplace_back(_object);
			break;
		}

		switch (_object->GetScene())
		{
		case SceneBase::title:
			mTitleObjects.emplace_back(_object);
			break;
		case SceneBase::tutorial:
			mTutorialObjects.emplace_back(_object);
			break;
		case SceneBase::easy:
			mStage01Objects.emplace_back(_object);
			break;
		}
	}
}

/*
@brief  �Q�[���I�u�W�F�N�g�̍폜
@param	�폜����GameObject�N���X�̃|�C���^
*/
void GameObjectManager::RemoveGameObject(GameObject* _object)
{
	auto iter = std::find(mPendingGameObjects.begin(), mPendingGameObjects.end(), _object);
	if (iter != mPendingGameObjects.end())
	{
		std::iter_swap(iter, mPendingGameObjects.end() - 1);
		mPendingGameObjects.pop_back();
	}

	iter = std::find(mTitleObjects.begin(), mTitleObjects.end(), _object);
	if (iter != mTitleObjects.end())
	{
		std::iter_swap(iter, mTitleObjects.end() - 1);
		mTitleObjects.pop_back();
	}

	iter = std::find(mTutorialObjects.begin(), mTutorialObjects.end(), _object);
	if (iter != mTutorialObjects.end())
	{
		std::iter_swap(iter, mTutorialObjects.end() - 1);
		mTutorialObjects.pop_back();
	}

	iter = std::find(mStage01Objects.begin(), mStage01Objects.end(), _object);
	if (iter != mStage01Objects.end())
	{
		std::iter_swap(iter, mStage01Objects.end() - 1);
		mStage01Objects.pop_back();
	}

}

void GameObjectManager::RemoveGameObjects(SceneBase::Scene _scene)
{
	switch (_scene)
	{
	case SceneBase::title:

		while (!mTitleObjects.empty())
		{
			delete mTitleObjects.back();
		}
		break;

	case SceneBase::tutorial:

		while (!mTutorialObjects.empty())
		{
			delete mTutorialObjects.back();
		}
		break;

	case SceneBase::easy:

		while (!mStage01Objects.empty())
		{
			delete mStage01Objects.back();
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