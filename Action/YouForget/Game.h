#pragma once

/*
* �Q�[���̐i�s���s���N���X
*/
class Game
{
public:
	// �R���X�g���N�^
	Game();
	// �f�X�g���N�^
	~Game() {};

	/// <summary>
	/// ����������
	/// </summary>
	/// <returns>true : ����, false : ���s</returns>
	bool Initialize();
	// �Q�[�����[�v
	void GameLoop();
	// �I������
	void Termination();

private:
	// ���͊֘A�̏���
	void ProcessInput();
	// �Q�[���̍X�V����
	void UpdateGame();
	// �`��֘A�̏���
	virtual void GenerateOutput();
	// ���[�h�����f�[�^�̉��
	void UnloadData();

	class SceneBase* mNowScene;				// ���݂̃V�[��
	class FPS* mFps;						// FPS�v���N���X
	class InputSystem* mInputSystem;		// ���͊Ǘ��N���X
	
	SceneBase::SceneType mReturnSceneType;	// �V�[���̍X�V���ɕԂ��Ă����V�[���^�C�v

	bool mRunningFlag;						// �Q�[���𑱂��邩�ǂ���(true:������)

	const float MWidth;						// ��ʂ̉���
	const float MHeight;					// ��ʂ̏c��

public:// �Q�b�^�[�Z�b�^�[
	/// <summary>
	/// �V�����V�[���𐶐�����
	/// </summary>
	/// <param name="_sceneType">�����������V�[���^�C�v</param>
	void SetNewScene(const SceneBase::SceneType _sceneType);
};