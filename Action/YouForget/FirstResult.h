#pragma once

/*
* FirstStage�̃��U���g�N���X
*/
class FirstResult : public ResultBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_nowScene">���݂̃V�[���^�C�v</param>
	FirstResult(const SceneType& _nowScene);
	// �f�X�g���N�^
	~FirstResult();

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
