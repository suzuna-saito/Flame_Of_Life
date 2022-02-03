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
	map<ItemNum, string> mItemDescription;

	// �`�悷��摜
	vector<string> mDescription;
	// �\�������摜��vector�ɕۑ����A�f�X�g���N�^�ł܂Ƃ߂ď���
	vector <Sprite*> mDeleteDescription;

	// ���̉摜��\�����邩
	bool mNextFlag;
	// �Ō�̉摜��\�����I�������
	bool mEndFlag;
	// �\�����������邩�ǂ���
	bool mDraw;

	// �o���摜�̃i���o�[
	unsigned int mNum ;

	// ���\�����Ă���摜
	Sprite* mNowDescription;
	// ���̉摜
	Sprite* mBackDescription;

	// �ǂ̃A�C�e��������Ă��邩��������
	void mSearch();
};
