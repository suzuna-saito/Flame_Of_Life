/*
@brief	�v���v���Z�b�T
*/
#pragma once

class SecondStage : public SceneBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_nowScene ���݂̃V�[��
	*/
	SecondStage(const Scene& _nowScene);

	/*
	@fn	�f�X�g���N�^
	*/
	~SecondStage();

	void Input(const InputState& state)override;

	/*
	@fn	���݂̃V�[�����ɖ��t���[���X�V����������
	*/
	SceneBase* update() override;

private:

};

