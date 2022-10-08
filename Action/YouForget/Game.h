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
	
	/// <summary>
	/// �I������
	/// </summary>
	void Termination();

	/// <summary>
	/// �Q�[�����[�v
	/// </summary>
	void GameLoop();
private:
	/// <summary>
	/// ���͊֘A�̏���
	/// </summary>
	void ProcessInput();

	/// <summary>
	/// �Q�[���̍X�V����
	/// </summary>
	void UpdateGame();

	/// <summary>
	/// �`��֘A�̏���
	/// </summary>
	virtual void GenerateOutput();

	/// <summary>
	/// ���[�h�����f�[�^�̉��
	/// </summary>
	void UnloadData();

	class SceneBase* mNowScene;			// ���݂̃V�[��
	class FPS* mFps;					// FPS�v���N���X
	class InputSystem* mInputSystem;	// ���͊Ǘ��N���X
	
	bool mRunningFlag;					// �Q�[���𑱂��邩�ǂ���(true:������)

	const float MWidth;					// ��ʂ̉���
	const float MHeight;				// ��ʂ̏c��

public:// �Q�b�^�[�Z�b�^�[

	/*
	@fn		�ŏ��̃V�[�������߂�֐�
	@param	_firstScene �ŏ��̃V�[��
	*/
	void SetFirstScene(SceneBase* _firstScene);
};

