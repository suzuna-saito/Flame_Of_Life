/*
@brief	�v���v���Z�b�T
*/
#pragma once

class EasyStage : public SceneBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_nowScene ���݂̃V�[��
	*/
	EasyStage(const Scene& _nowScene);

	/*
	@fn	�f�X�g���N�^
	*/
	~EasyStage();

	void Input(const InputState& state)override;

	/*
	@fn	���݂̃V�[�����ɖ��t���[���X�V����������
	*/
	SceneBase* update() override;

private:

};

