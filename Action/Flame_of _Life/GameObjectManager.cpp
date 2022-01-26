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

	// Easy�X�e�[�W���X�V����
	for (auto easystageObject : mEasyStageObjects)
	{
		easystageObject->Update(_deltaTime);
	}
	// Norma�X�e�[�W���X�V����
	for (auto normalstageObject : mNormalStageObjects)
	{
		normalstageObject->Update(_deltaTime);
	}
	// Hard�X�e�[�W���X�V����
	for (auto hardstageObject : mHardStageObjects)
	{
		hardstageObject->Update(_deltaTime);
	}
	// ���U���g�X�e�[�W���X�V����
	for (auto resultObject : mResultObjects)
	{
		resultObject->Update(_deltaTime);
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
			mEasyStageObjects.emplace_back(pending);
		}
		if (pending->GetScene() == SceneBase::Scene::normal)
		{
			mNormalStageObjects.emplace_back(pending);
		}
		if (pending->GetScene() == SceneBase::Scene::hard)
		{
			mHardStageObjects.emplace_back(pending);
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
		case Tag::Camera:
			mCameraObjects.emplace_back(_object);
			break;
		}

		switch (_object->GetScene())
		{
		case SceneBase::Scene::title:
			mTitleObjects.emplace_back(_object);
			break;
		case SceneBase::Scene::tutorial:
			mTutorialObjects.emplace_back(_object);
			break;
		case SceneBase::Scene::easy:
			mEasyStageObjects.emplace_back(_object);
			break;
		case SceneBase::Scene::normal:
			mNormalStageObjects.emplace_back(_object);
			break;
		case SceneBase::Scene::hard:
			mHardStageObjects.emplace_back(_object);
			break;
		case SceneBase::Scene::result:
			mResultObjects.emplace_back(_object);
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

	// �^�C�g���V�[��
	iter = std::find(mTitleObjects.begin(), mTitleObjects.end(), _object);
	if (iter != mTitleObjects.end())
	{
		std::iter_swap(iter, mTitleObjects.end() - 1);
		mTitleObjects.pop_back();
	}
	// �`���[�g���A��
	iter = std::find(mTutorialObjects.begin(), mTutorialObjects.end(), _object);
	if (iter != mTutorialObjects.end())
	{
		std::iter_swap(iter, mTutorialObjects.end() - 1);
		mTutorialObjects.pop_back();
	}
	// Easy�V�[��
	iter = std::find(mEasyStageObjects.begin(), mEasyStageObjects.end(), _object);
	if (iter != mEasyStageObjects.end())
	{
		std::iter_swap(iter, mEasyStageObjects.end() - 1);
		mEasyStageObjects.pop_back();
	}
	// Normal�V�[��
	iter = std::find(mNormalStageObjects.begin(), mNormalStageObjects.end(), _object);
	if (iter != mNormalStageObjects.end())
	{
		std::iter_swap(iter, mNormalStageObjects.end() - 1);
		mNormalStageObjects.pop_back();
	}
	// Hard�V�[��
	iter = std::find(mHardStageObjects.begin(), mHardStageObjects.end(), _object);
	if (iter != mHardStageObjects.end())
	{
		std::iter_swap(iter, mHardStageObjects.end() - 1);
		mHardStageObjects.pop_back();
	}
	// ���U���g�V�[��
	iter = std::find(mResultObjects.begin(), mResultObjects.end(), _object);
	if (iter != mResultObjects.end())
	{
		std::iter_swap(iter, mResultObjects.end() - 1);
		mResultObjects.pop_back();
	}

}

void GameObjectManager::RemoveGameObjects(SceneBase::Scene _scene)
{
	switch (_scene)
	{
	case SceneBase::Scene::title:

		while (!mTitleObjects.empty())
		{
			delete mTitleObjects.back();
		}
		break;

	case SceneBase::Scene::tutorial:

		while (!mTutorialObjects.empty())
		{
			delete mTutorialObjects.back();
		}
		break;

	case SceneBase::Scene::easy:

		while (!mEasyStageObjects.empty())
		{
			delete mEasyStageObjects.back();
		}
		break;

	case SceneBase::Scene::normal:

		while (!mNormalStageObjects.empty())
		{
			delete mNormalStageObjects.back();
		}
		break;

	case SceneBase::Scene::hard:

		while (!mHardStageObjects.empty())
		{
			delete mHardStageObjects.back();
		}
		break;

	case SceneBase::Scene::result:

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