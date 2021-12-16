#pragma once

class ItemBase;

class Result :public SceneBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_nowScene ���݂̃V�[��
	*/
	Result(const Scene& _nowScene);

	/*
	@fn	�f�X�g���N�^
	*/
	~Result();

	/*
	@fn	�^�C�g���V�[�����ɖ��t���[���X�V����������
	*/
	SceneBase* update() override;

	/*
	@fn	�^�C�g���V�[�����ɖ��t���[�����͏���������
	*/
	void Input(const InputState& _inputState)override;

private:
	// �}�b�v�Ŏ擾�����A�C�e���Ɛ������֘A�t����
	map<itemNames, const char*> mItemDescription;

	// �`�悷�����
	vector<const char*> mDescription;

	// �C�e���[�^�[
	decltype(mItemDescription)::iterator it;

	bool mFirstFlag;

	//vector<itemNames> test;
};
