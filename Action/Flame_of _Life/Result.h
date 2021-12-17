#pragma once

class Sprite;

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
	map<itemNames, string> mItemDescription;

	// �`�悷�����
	vector<string> mDescription;

	// ��񂾂����Ăق�������
	bool mFirstFlag;
	bool mDraw;
	bool mBackDraw;

	// ��������
	int mCount;
	int mNum;

	Sprite* mNowDescription;
	Sprite* mBackDescription;
	//vector<itemNames> test;
};
