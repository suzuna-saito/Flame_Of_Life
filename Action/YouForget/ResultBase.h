#pragma once

class Sprite;

// ���U���g�̃x�[�X�N���X
class ResultBase :public SceneBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_nowScene ���݂̃V�[��
	*/
	ResultBase(const Scene& _nowScene);

	/*
	@fn	�f�X�g���N�^
	*/
	~ResultBase();

protected:
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
	unsigned int mNum;

	// ���\�����Ă���摜
	Sprite* mNowDescription;
	// ���̉摜
	Sprite* mBackDescription;

	// �ǂ̃A�C�e��������Ă��邩��������
	void mSearch();
	// ���̉摜���o������
	void mDrawUpdate();
	// ���̃V�[���Ɉڂ邩�A�܂��摜���o����Update����
	void mResultUpdate();
};
