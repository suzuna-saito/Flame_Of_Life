#pragma once

/*
* ���U���g�̊��N���X
*/
class ResultBase :public SceneBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_nowScene ���݂̃V�[��
	*/
	ResultBase(const SceneType& _nowScene);

	/*
	@fn	�f�X�g���N�^
	*/
	~ResultBase();

	/*
	@fn	�^�C�g���V�[�����ɖ��t���[���X�V����������
	*/
	SceneBase* update() override;

	// �G���h�̕���t���O
	static bool mClearEndFlag;

	// @@@
	//static Sprite* mEndSprite;

protected:

	// �}�b�v�Ŏ擾�����A�C�e���Ɛ������֘A�t����
	map<ItemNum, string> mPuzzlePieces;

	// �ǂ̃A�C�e��������Ă��邩��������
	void mSearch();
	// ���̉摜���o������
	void mDrawUpdate();
	// ���̃V�[���Ɉڂ邩�A�܂��摜���o����Update����
	void mResultUpdate();

	class PuzzleUI* mPuzzleUI;			// �p�Y����UI
private:

	// �`�悷��摜
	vector<string> mDescription;
	// �v���C���Ɏ擾�����p�Y���s�[�X�̉摜�f�[�^
	vector<string> mGetPieces;
	// �\�������摜��vector�ɕۑ����A�f�X�g���N�^�ł܂Ƃ߂ď���
	vector <class FullPicture*> mDeleteDescription;

	// �\�����������邩�ǂ���
	bool mDraw;

	// �o���摜�̃i���o�[
	unsigned int mNum;

	// ���\�����Ă���摜
	class FullPicture* mNowDescription;
	// �{�^����UI
	class AButtonUI* mButton;

	////�{�^���摜��UI
	//ButtonUI* mButtonUI;
};
