/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_nowScene ���݂̃V�[��
*/
ResultBase::ResultBase(const Scene& _nowScene)
	:SceneBase()
	, mDescription()
	, mDeleteDescription()
	, mNextFlag(false)
	, mEndFlag(false)
	, mDraw(false)
	, mNowDescription(nullptr)
{
	SetScene(_nowScene);

	// ��Ԍ��̉摜
	mBackDescription = new Sprite("Assets/UI/BackPicture.png");
}

/*
@fn	�f�X�g���N�^
*/
ResultBase::~ResultBase()
{
	// �擾�����A�C�e���̒��Ƀf�[�^�������Ă����
	if (ItemBase::mGetNumber.size() != 0)
	{
		ItemBase::mGetNumber.clear();
	}

	// ���������f�[�^�������Ă�����
	int size = mDeleteDescription.size();
	for (int i = 0; i < size; i++)
	{
		delete mDeleteDescription[i];
	}

	delete mSprite;
	delete mBackDescription;
}

void ResultBase::mDrawUpdate()
{
	// �Ō�̐����܂Ō����Ă���
	if (mEndFlag)
	{
		// �V�[���J�ڃt���O��true�ɂ���
		mGameSceneFlag = true;
	}

	// �Ō�̐����܂ŕ`��ł��ĂȂ�������
	if (mNum < mDescription.size())
	{
		// ���̐������o���悤�ɂ���
		mDraw = true;
	}
	else
	{
		mEndFlag = true;
	}
}

void ResultBase::mResultUpdate()
{
	// �ۑ���������
	if (mNum < mDescription.size())
	{
		// mDraw��true�̎�
		if (mDraw)
		{
			// �V�����摜���o��
			mNowDescription = new Sprite(mDescription[mNum]);
			// ��xnew������AmDraw��false�ɂ���B
			mDraw = false;

			++mNum;

			// �f�X�g���N�^�ō폜����悤��vector�ɕۑ����Ă���
			mDeleteDescription.push_back(mNowDescription);
		}
	}
	// �ۑ��������\�����I�������
	if (mEndFlag)
	{
		// �����Ȃ��Ⴂ���Ȃ��摜�������
		if (mDeleteDescription.size() != 0)
		{
			for (unsigned int i = 0; i < mDeleteDescription.size(); i++)
			{
				// �\�������摜��S�ē����ɂ���
				mDeleteDescription[i]->NotVisible();
			}
		}

		mBackDescription->NotVisible();

		//�@�I���̉摜��\�����ĂȂ����
		if (mSprite == nullptr)
		{
			mSprite = new Sprite("Assets/UI/End.png");
		}
	}

}

void ResultBase::mSearch()
{
	// �C�e���[�^�[
	decltype(mItemDescription)::iterator it;

	// �擾�����A�C�e������
	for (const auto& num : ItemBase::mGetNumber)
	{
		// �T��
		it = mItemDescription.find(num);

		// ��������
		if (it != mItemDescription.end())
		{
			// mDescription�Ɍ��������������ۑ�
			mDescription.push_back(mItemDescription[num]);
		}
	}
}