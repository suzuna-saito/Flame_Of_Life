/*
@brief	�v���v���Z�b�T
*/
#pragma once

class ThirdStage : public SceneBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_nowScene ���݂̃V�[��
	*/
	ThirdStage(const Scene& _nowScene);

	/*
	@fn	�f�X�g���N�^
	*/
	~ThirdStage();

	void Input(const InputState& state)override;

	/*
	@fn	���݂̃V�[�����ɖ��t���[���X�V����������
	*/
	SceneBase* update() override;

private:

};

