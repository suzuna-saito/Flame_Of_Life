/*
@brief	�v���v���Z�b�T
*/
#pragma once

class Stage01 : public SceneBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_nowScene ���݂̃V�[��
	*/
	Stage01(const Scene& _nowScene);

	/*
	@fn	�f�X�g���N�^
	*/
	~Stage01();

	void Input(const InputState& state)override;

	/*
	@fn	���݂̃V�[�����ɖ��t���[���X�V����������
	*/
	SceneBase* update() override;

private:

};

