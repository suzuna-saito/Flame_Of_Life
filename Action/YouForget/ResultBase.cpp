#include "pch.h"

// �ÓI�����o�ϐ��̏�����
bool ResultBase::mClearEndFlag = true;	// �G���h�̕���t���O(true:�N���A)

ResultBase::ResultBase(const SceneType& _nowScene)
	: SceneBase(_nowScene)
	, mNowDrawTextUI(nullptr)
{
	mIsSceneType = _nowScene;

	// A�{�^����UI�𐶐�
	new AButtonUI();
}

ResultBase::~ResultBase()
{
	// �V�[����J�ڂ���O�Ɏ擾�����p�Y���s�[�X��0�ɖ߂�
	PuzzlePiece::mGetNumber.clear();
}

void ResultBase::Search()
{
	// �擾�����p�Y���s�[�X����
	decltype(mPuzzlePieceDatas)::iterator it;
	for (const auto& num : PuzzlePiece::mGetNumber)
	{
		// �L�[����v������̂�T��
		it = mPuzzlePieceDatas.find(num);

		// ��v������
		if (it != mPuzzlePieceDatas.end())
		{
			// �s�[�X�̉摜�f�[�^�ۑ�
			StoresData(mPuzzlePieceDatas[num], UIBase::UIType::ePuzzlePiece);
		}
	}
}

bool ResultBase::Collected()
{
	// �S�Ẵs�[�X������ł��ĂȂ�������
	if (mPictureDatas.size() != mPuzzlePieceDatas.size())
	{
		// �擾�����s�[�X��1�ȉ���������
		if (mPictureDatas.size() <= 1)
		{
			// ����o���Ȃ������p�̃e�L�X�g�摜 1 ��ǉ��i�[
			StoresData("Assets/UI/ResultBase/BadWord.png", UIBase::UIType::eText);
		}
		// �擾�����s�[�X��2�ȏゾ������
		else
		{
			// ����o���Ȃ������p�̃e�L�X�g�摜 2 ��ǉ��i�[
			StoresData("Assets/UI/ResultBase/BadWord2.png", UIBase::UIType::eText);
		}
		
		// �N���A�t���O��false�ɂ���
		mClearEndFlag = false;

		return false;
	}
	
	return true;
}

void ResultBase::StoresData(const string _filename, const int _uiType)
{
	// �`�悵�����摜�f�[�^�Ƃ��̉摜��UI�^�C�v���֘A�t���Ċi�[
	mPictureDatas[_filename] = _uiType;
	// �L�[�i�t�@�C�����j���i�[
	mFileNames.emplace_back(_filename);
}

bool ResultBase::mDrawUpdate()
{
	// mFileNames�̒����󂾂�����
	if (mFileNames.empty())
	{
		// mNowDrawTextUI���󂶂�Ȃ�������
		if (mNowDrawTextUI != nullptr)
		{
			// ���`�悵�Ă���e�L�X�g�̕`�����߂�
			mNowDrawTextUI->SetThisVisible(false);
		}
		// �����S�ĕ`�悵���̂�true��Ԃ�
		return true;
	}

	// mPictureDatas�̒l��ePuzzlePiece��������
	if (mPictureDatas[mFileNames[0]] == UIBase::UIType::ePuzzlePiece)
	{
		// �p�Y���s�[�X�𐶐�
		new PuzzleUI(mFileNames[0], UIBase::UIType::ePuzzlePiece);
	}
	// mPictureDatas�̒l��eText��������
	else if (mPictureDatas[mFileNames[0]] == UIBase::UIType::eText)
	{
		// mNowDrawTextUI���󂶂�Ȃ�������
		if (mNowDrawTextUI != nullptr)
		{
			// ���`�悵�Ă���e�L�X�g�̕`�����߂�
			mNowDrawTextUI->SetThisVisible(false);
		}

		// �e�L�X�g�摜�𐶐�
		mNowDrawTextUI = new Text(mFileNames[0]);
	}

	// (�������łɕ`�悵���t�@�C���Ȃ̂�)mFileNames�̐擪�v�f���폜
	mFileNames.erase(mFileNames.begin());

	return false;
}