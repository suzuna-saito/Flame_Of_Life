/*
@brief	�v���v���Z�b�T
*/
#pragma once

class Tutorial : public SceneBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_nowScene ���݂̃V�[��
	*/
	Tutorial(const Scene& _nowScene);

	/*
	@fn	�f�X�g���N�^
	*/
	~Tutorial();

	void Input(const InputState& state)override;

	/*
	@fn	���݂̃V�[�����ɖ��t���[���X�V����������
	*/
	SceneBase* update() override;

private:
	
};
