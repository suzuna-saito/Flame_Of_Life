/*
@brief	�v���v���Z�b�T
*/
#pragma once

class HardStage : public SceneBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_nowScene ���݂̃V�[��
	*/
	HardStage(const Scene& _nowScene);

	/*
	@fn	�f�X�g���N�^
	*/
	~HardStage();

	void Input(const InputState& state)override;

	/*
	@fn	���݂̃V�[�����ɖ��t���[���X�V����������
	*/
	SceneBase* update() override;

private:

};

