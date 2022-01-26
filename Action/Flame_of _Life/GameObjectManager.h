/*
@file	GameObjectManager.h
@brief	�Q�[���I�u�W�F�N�g�̍X�V���s��
*/

/*
@brief	�v���v���Z�b�T
*/
#pragma once

#define GAME_OBJECT_MANAGER GameObjectManager::GetInstance()


class GameObjectManager
{
public:

	/*
	@return ���g�̃C���X�^���X��Ԃ�
	*/
	static GameObjectManager* GetInstance() { return mManager; }

	/*
	@fn �C���X�^���X�𐶐�
	*/
	static void CreateInstance();

	/*
	@fn �C���X�^���X���폜
	*/
	static void DeleteInstance();

	/*
	@fn		�Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g����
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime);

	/*
	@fn		�Q�[���I�u�W�F�N�g�̓��͏���
	@param	_state �e���͋@��̓��͏��
	@brief	�L�[�{�[�h�A�}�E�X�A�R���g���[���[
	*/
	void ProcessInput(const InputState& _state);

	/*
	@fn		�Q�[���I�u�W�F�N�g�̒ǉ�
	@param	_object �ǉ�����GameObject�N���X�̃|�C���^
	*/
	void AddGameObject(GameObject* _object);

	/*
	@fn		�Q�[���I�u�W�F�N�g�̍폜
	@param	_object �폜����GameObject�N���X�̃|�C���^
	*/
	void RemoveGameObject(GameObject* _object);

	/*
	@fn		�V�[�����Ƃ̑S�ẴQ�[���I�u�W�F�N�g�̍폜
	@param	_scene �폜����V�[���̃^�O
	*/
	void RemoveGameObjects(SceneBase::Scene _scene);

	/*
	@fn		�g�p�������ׂẴQ�[���I�u�W�F�N�g���������
	@detail �V�[���J�ڂ̍ۂɎg�p�����BGameObject���̍ė��p�t���O�������Ă���I�u�W�F�N�g�͉�����Ȃ�
	*/
	void RemoveAllUsedGameObject();

	/*
	@fn		����̃Q�[���I�u�W�F�N�g��T��
	@param	_tag �Q�[���I�u�W�F�N�g�̃^�O
	*/
	GameObject* FindGameObject(Tag _tag);

	/*
	@fn		����̃Q�[���I�u�W�F�N�g��T��
	@param	_tag �Q�[���I�u�W�F�N�g�̃^�O
	*/
	std::vector<GameObject*> FindGameObjects(Tag _tag);

private:

	/*
	@fn	�R���X�g���N�^
	*/
	GameObjectManager();

	/*
	@fn	�f�X�g���N�^
	*/
	~GameObjectManager();

	//���g�̃C���X�^���X
	static GameObjectManager* mManager;

	//�Q�[���I�u�W�F�N�g�̃|�C���^�̉ϒ��R���e�i
	//�J�������i�[���邽�߂̉ϒ��R���e�i
	std::vector<GameObject*> mCameraObjects;
	//�^�C�g�����̑S�ẴQ�[���I�u�W�F�N�g���i�[���邽�߂̉ϒ��R���e�i
	std::vector<GameObject*> mTitleObjects;
	//�`���[�g���A�����̑S�ẴQ�[���I�u�W�F�N�g���i�[���邽�߂̉ϒ��R���e�i
	std::vector<GameObject*> mTutorialObjects;
	//Easy�X�e�[�W�̎��̑S�ẴQ�[���I�u�W�F�N�g���i�[���邽�߂̉ϒ��R���e�i
	std::vector<GameObject*> mEasyStageObjects;
	//Normal�X�e�[�W�̎��̑S�ẴQ�[���I�u�W�F�N�g���i�[���邽�߂̉ϒ��R���e�i
	std::vector<GameObject*> mNormalStageObjects;
	//Hard�X�e�[�W�̎��̑S�ẴQ�[���I�u�W�F�N�g���i�[���邽�߂̉ϒ��R���e�i
	std::vector<GameObject*> mHardStageObjects;
	//���U���g���̑S�ẴQ�[���I�u�W�F�N�g���i�[���邽�߂̉ϒ��R���e�i
	std::vector<GameObject*> mResultObjects;
	//Update���ɒǉ����ꂽ�Q�[���I�u�W�F�N�g�̃|�C���^���ꎞ�I�ɕۑ�����ϒ��R���e�i
	std::vector<GameObject*> mPendingGameObjects;

	//Update�����ǂ���
	bool mUpdatingGameObject;

};
