#pragma once

/*
* ���U���g�̊��N���X
*/
class ResultBase :public SceneBase
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_nowScene">���݂̃V�[���^�C�v</param>
	ResultBase(const SceneType& _nowScene);
	// �f�X�g���N�^
	~ResultBase();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <returns>���̃V�[���̃|�C���^</returns>
	SceneBase* update() override;

	static bool mClearEndFlag;	// �G���h�̕���t���O(true:�N���A)

protected:
	// �ǂ̃A�C�e��������Ă��邩��������
	void mSearch();
	// ���̉摜���o������
	void mDrawUpdate();
	// ���̃V�[���Ɉڂ邩�A�܂��摜���o����Update����
	void mResultUpdate();

	map<ItemNum, string> mPuzzlePieces;	// �s�[�X�ƕK�v�ȉ摜�f�[�^���֘A�t���Ċi�[
	class PuzzleUI* mPuzzleUI;			// �p�Y����UI
private:
	/// <summary>
	/// �`�悵�����摜�f�[�^��ǉ�����
	/// </summary>
	/// <param name="_uiType">�摜��UI�^�C�v</param>
	/// <param name="_filename">�摜�̃t�@�C����</param>
	void AddPictureData(const UIBase::UIType _uiType, const string _filename);

	class Text* mTextUI;										// �e�L�X�g�摜��UI

	unordered_multimap<UIBase::UIType, string> mPictureDatas;	// �`�悵�����摜�f�[�^�Ƃ��̉摜��UI�^�C�v���֘A�t���Ċi�[(�L�[�d��OK)
	//vector<string> mGetPieces;								// �v���C���Ɏ擾�����p�Y���s�[�X�̉摜�f�[�^���i�[
	//// �`�悷��摜
	//vector<string> mDescription;
	//// �\�������摜��vector�ɕۑ����A�f�X�g���N�^�ł܂Ƃ߂ď���
	//vector <class FullPicture*> mDeleteDescription;

	//// �\�����������邩�ǂ���
	//bool mDraw;

	//// �o���摜�̃i���o�[
	//unsigned int mNum;

	//// ���\�����Ă���摜
	//class FullPicture* mNowDescription;
	//// �{�^����UI
	//class AButtonUI* mAButton;

	//////�{�^���摜��UI
	////ButtonUI* mButtonUI;
};
