/*
@brief	�v���v���Z�b�T
*/
#pragma once


class TitleScene : public SceneBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_nowScene ���݂̃V�[��
	*/
	TitleScene(const Scene& _nowScene);

	/*
	@fn	�f�X�g���N�^
	*/
	~TitleScene();

	/*
	@fn	�^�C�g���V�[�����ɖ��t���[���X�V����������
	*/
	SceneBase* update() override;

	/*
	@fn	�^�C�g���V�[�����ɖ��t���[�����͏���������
	*/
	void Input(const InputState& _inputState)override;

private:

	bool mGameSceneFlag;
};

