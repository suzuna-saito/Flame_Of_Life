#pragma once

class Sprite;

class testResult :public SceneBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_nowScene ���݂̃V�[��
	*/
	testResult(const Scene& _nowScene);

	/*
	@fn	�f�X�g���N�^
	*/
	~testResult();

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

	// ���̐�����\�����邩
	bool mNextFlag;
	// �Ō�̐�����\�����I�������
	bool mEndFlag;
	// ��񂾂����Ăق�������
	bool mDraw;

	// �o�������̃i���o�[
	int mNum;

	Sprite* mNowDescription;

	vector <Sprite*> mDeleteDescription;
	Sprite* mNowDescriptionOne;
	Sprite* mNowDescriptionTwo;
	Sprite* mNowDescriptionThree;
	Sprite* mBackDescription;

	// �ǂ̃A�C�e��������Ă��邩��������
	void mInit();
};
