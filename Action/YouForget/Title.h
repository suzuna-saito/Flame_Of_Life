#pragma once

/*
* Title�̍X�V
*/
class Title : public SceneBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_nowScene">���݂̃V�[���^�C�v</param>
	Title(const SceneType& _nowScene);
	// �f�X�g���N�^
	~Title();

	/// <summary>
	/// ���͏���
	/// </summary>
	/// <param name="_inputState">���͏��</param>
	void Input(const InputState& _inputState)override;
	/// <summary>
	/// �X�V����
	/// </summary>
	/// <returns></returns>
	SceneBase* update() override;
};

