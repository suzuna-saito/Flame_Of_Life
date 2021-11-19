/*
@file Game.h
@brief �Q�[���̐i�s���s��
*/

/*
@brief	�v���v���Z�b�T
*/
#pragma once

class FPS;
class InputSystem;

class Game
{
public:

	/*
	@fn	�R���X�g���N�^
	*/
	Game();

	/*
	@fn	�f�X�g���N�^
	*/
	~Game() {};

	/*
	@fn		����������
	@return true : ����, false : ���s(bool�^)
	*/
	bool Initialize();

	/*
	@fn	�I������
	*/
	void Termination();

	/*
	@fn	�Q�[�����[�v
	*/
	void GameLoop();

	//�V�[����؂�ւ��邩
	bool mSceneFlag;

private:

	//���݂̃V�[��
	SceneBase* mNowScene;

	/*
	@fn	���͊֘A�̏���
	*/
	void ProcessInput();

	/*
	@fn	�`��֘A�̏���
	*/
	virtual void GenerateOutput();

	/*
	@fn	�Q�[���̍X�V����
	*/
	void UpdateGame();

	/*
	@fn	���[�h�����f�[�^�̉��
	*/
	void UnloadData();

	//FPS�v���N���X
	FPS* mFps;
	//���͊Ǘ��N���X
	InputSystem* mInputSystem;
	//�Q�[���𑱂��邩�ǂ���
	bool mRunningFlag;

	const float MWidth;
	const float MHeight;
public://�Q�b�^�[�Z�b�^�[

	/*
	@fn		�ŏ��̃V�[�������߂�֐�
	@param	_firstScene �ŏ��̃V�[��
	*/
	void SetFirstScene(SceneBase* _firstScene);
};

