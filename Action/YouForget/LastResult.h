#pragma once

/*
* �Q�[���N���A���Q�[���I�[�o�[���������̍X�V���s���N���X
*/
class LastResult :public ResultBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_nowScene ���݂̃V�[��
	*/
	LastResult(const SceneType& _nowScene);

	/*
	@fn	�f�X�g���N�^
	*/
	~LastResult();

	/*
	@fn	�^�C�g���V�[�����ɖ��t���[���X�V����������
	*/
	SceneBase* update() override;

	/*
	@fn	�^�C�g���V�[�����ɖ��t���[�����͏���������
	*/
	void Input(const InputState& _inputState)override;
};
