#pragma once

/*
* SecondStage�̃��U���g�N���X
*/
class SecondResult :public ResultBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_nowScene">���݂̃V�[���^�C�v</param>
	SecondResult(const SceneType& _nowScene);
	// �f�X�g���N�^
	~SecondResult();

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