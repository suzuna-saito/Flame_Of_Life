#pragma once

/*
* �Q�[���N���A���Q�[���I�[�o�[���������̍X�V���s���N���X
*/
class LastResult :public ResultBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_nowScene">���݂̃V�[���^�C�v</param>
	LastResult(const SceneType& _nowScene);
	// �f�X�g���N�^
	~LastResult();

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
