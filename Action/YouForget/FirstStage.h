/*
@brief	�v���v���Z�b�T
*/
#pragma once

class FirstStage : public SceneBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_nowScene ���݂̃V�[��
	*/
	FirstStage(const Scene& _nowScene);

	/*
	@fn	�f�X�g���N�^
	*/
	~FirstStage();

	void Input(const InputState& state)override;

	/*
	@fn	���݂̃V�[�����ɖ��t���[���X�V����������
	*/
	SceneBase* update() override;

private:

};

