#pragma once

class ThirdResult :public ResultBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_nowScene ���݂̃V�[��
	*/
	ThirdResult(const Scene& _nowScene);

	/*
	@fn	�f�X�g���N�^
	*/
	~ThirdResult();

	/*
	@fn	�^�C�g���V�[�����ɖ��t���[���X�V����������
	*/
	SceneBase* update() override;

	/*
	@fn	�^�C�g���V�[�����ɖ��t���[�����͏���������
	*/
	void Input(const InputState& _inputState)override;
};
