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
	/// <returns>���̃V�[���̃^�C�v</returns>
	SceneType update() override { return SceneType::eInit; }

	static bool mClearEndFlag;	// �G���h�̕���t���O(true:�N���A)

protected:
	// �ǂ̃p�Y���s�[�X���擾���Ă��邩�������A�擾�����f�[�^�͊i�[����
	void Search();	
	/// <summary>
	/// �擾���ɉ����ăt���O��Ԃ�
	/// </summary>
	/// <returns>true : �p�Y���s�[�X��S�ĉ�����Ă���</returns>
	bool Collected();

	/// <summary>
	/// �`�悵�����摜�f�[�^���i�[����
	/// </summary>
	/// <param name="_filename">�摜�̃t�@�C����</param>
	/// <param name="_uiType">�摜��UI�^�C�v</param>
	void StoresData(const string _filename, const int _uiType);
	/// <summary>
	/// mFileNames�Ɋi�[����Ă���f�[�^������`�悷��
	/// </summary>
	/// <returns>true : �S�ĕ`�悵��</returns>
	bool mDrawUpdate();

	map<ItemNum, string> mPuzzlePieceDatas;	// �s�[�X�ƕK�v�ȉ摜�f�[�^���֘A�t���Ċi�[
private:
	class Text* mNowDrawTextUI;				// ���`�悵���Ă���e�L�X�g�摜��UI

	map<string, int> mPictureDatas;			// �`�悵�����摜�f�[�^�Ƃ��̉摜��UI�^�C�v���֘A�t���Ċi�[
	vector<string> mFileNames;				// mPictureDatas�ɃL�[�Ƃ��Ċi�[�����S�Ẵt�@�C����(�`�悵�����t�@�C��)
};
