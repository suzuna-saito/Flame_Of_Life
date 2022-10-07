#pragma once

// ���U���g�̃x�[�X�N���X
class ResultBase :public SceneBase
{
public:
	// �R���X�g���N�^
	ResultBase();
	// �f�X�g���N�^
	~ResultBase();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <returns>���̃V�[���̃|�C���^��Ԃ�</returns>
	SceneBase* update() override;

	static bool mClearEndFlag; // �G���h�̕���t���O(true : �N���A)

protected:
	// �ǂ̃s�[�X���擾����������������
	void mSearch();
	// ���̉摜���o������
	void mDrawUpdate();
	// ���̃V�[���Ɉڂ邩�A�܂��摜���o����Update����
	void mResultUpdate();

	map<ItemNum, string> mPuzzles;	// �擾�����p�Y���s�[�X��UI���֘A�t����

private:
	vector<string> mPictures;	// �`�悷��摜

	bool mDraw;					// �\�����������邩�ǂ���
	
	unsigned int mNum;			// �o���摜�̃i���o�[

	class FullPicture* mNowDescription;	// ���邩�H
	class AButtonUI * mAButton;			// A�{�^����UI
};
