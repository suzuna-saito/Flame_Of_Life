/*
@brief	�v���v���Z�b�T
*/
#pragma once

class NormalStage : public SceneBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_nowScene ���݂̃V�[��
	*/
	NormalStage(const Scene& _nowScene);

	/*
	@fn	�f�X�g���N�^
	*/
	~NormalStage();

	void Input(const InputState& state)override;

	/*
	@fn	���݂̃V�[�����ɖ��t���[���X�V����������
	*/
	SceneBase* update() override;

private:

};

