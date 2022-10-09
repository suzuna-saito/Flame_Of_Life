#pragma once

/*
* SecondStage�̍X�V
*/
class SecondStage : public SceneBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_nowScene">���݂̃V�[���^�C�v</param>
	SecondStage(const SceneType& _nowScene);
	// �f�X�g���N�^
	~SecondStage();

	/// <summary>
	/// ���͏���
	/// </summary>
	/// <param name="_inputState">���͏��</param>
	void Input(const InputState& _inputState)override;
	/// <summary>
	/// �X�V����
	/// </summary>
	/// <returns>���̃V�[���̃^�C�v</returns>
	SceneType update() override;
};