#pragma once

class SecondResult :public ResultBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_nowScene ���݂̃V�[��
	*/
	SecondResult(const Scene& _nowScene);

	/*
	@fn	�f�X�g���N�^
	*/
	~SecondResult();

	/*
	@fn	�^�C�g���V�[�����ɖ��t���[���X�V����������
	*/
	SceneBase* update() override;

	/*
	@fn	�^�C�g���V�[�����ɖ��t���[�����͏���������
	*/
	void Input(const InputState& _inputState)override;
};
