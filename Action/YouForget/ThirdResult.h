#pragma once

/*
* ThirdStage�̃��U���g�N���X
*/
class ThirdResult :public ResultBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_nowScene">���݂̃V�[���^�C�v</param>
	ThirdResult(const SceneType& _nowScene);
	// �f�X�g���N�^
	~ThirdResult();

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