/*
@brief	�C���N���[�h
*/
#include "pch.h"

bool ResultBase::mClearEndFlag = true;
//Sprite* ResultBase::mEndSprite;

/*
@fn		�R���X�g���N�^
@param	_nowScene ���݂̃V�[��
*/
ResultBase::ResultBase()
	:SceneBase()
	, mPictures()
	//, mDeleteDescription()
	, mDraw(false)
	, mNowDescription(nullptr)
	, mAButton(nullptr)
	, mNum(0)
{
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
}

/*
@fn	���݂̃V�[�����ɖ��t���[���X�V����������
*/
SceneBase* ResultBase::update()
{
	return nullptr;
}

void ResultBase::mSearch()
{
	// �C�e���[�^�[
	decltype(mPuzzles)::iterator it;

	// �擾�����A�C�e������
	for (const auto& num : ItemBase::mGetNumber)
	{
		// �T��
		it = mPuzzles.find(num);

		// ��������
		if (it != mPuzzles.end())
		{
			// mDescription�Ɍ��������������ۑ�
			mPictures.push_back(mPuzzles[num]);
		}
	}

	// �S�Ẵs�[�X������ł��ĂȂ�������
	if (SceneBase::mIsScene != SceneType::eGameClear &&
		mPictures.size() != 3)
	{
		mPictures.push_back("Assets/UI/ResultBase/BadWord.png");
		mClearEndFlag = false;
	}
	else
	{
		// �V�[���ɂ���čX�ɉ摜��ǉ�
		switch (SceneBase::mIsScene)
		{
		case SceneType::eFirstResult:
			mPictures.push_back("Assets/UI/FirstResult/Word_1.png");
			mPictures.push_back("Assets/UI/FirstResult/Word_2.png");
			break;
		case SceneType::eSecondResult:
			mPictures.push_back("Assets/UI/SecondResult/Word_1.png");
			mPictures.push_back("Assets/UI/SecondResult/Word_2.png");
			break;
		case SceneType::eThirdResult:
			mPictures.push_back("Assets/UI/ThirdResult/Word_1.png");
			mPictures.push_back("Assets/UI/ThirdResult/Word_2.png");
			break;
		case SceneType::eGameClear:
			if (mClearEndFlag)
			{
				mPictures.push_back("Assets/UI/EndResult/Clear_2.png");
				mPictures.push_back("Assets/UI/EndResult/Clear_3.png");
			}
			break;
		default:
			break;
		}
	}
}

void ResultBase::mDrawUpdate()
{
	// ���̐������o���悤�ɂ���
	mDraw = true;

	if (SceneBase::mIsScene == SceneType::eGameClear)
	{
		if (SceneBase::mIsScene == SceneType::eGameClear && mFullPicture != nullptr)
		{
			mFullPicture->SetThisVisible(false);
		}

		if (mNowDescription != nullptr)
		{
			mNowDescription->SetThisVisible(false);
		}
	}
}

void ResultBase::mResultUpdate()
{
	// mDraw��true�̎�
	if (mDraw)
	{
		if (mNum == mPictures.size())
		{
			// �V�[���J�ڃt���O��true�ɂ���
			mGameSceneFlag = true;
		}
		else
		{
			// @@@
			if (mNum == 4)
			{
				mNowDescription->SetThisVisible(false);
			}
			// �V�����摜���o��
			mNowDescription = new FullPicture(mPictures[mNum]);
			// ��xnew������AmDraw��false�ɂ���B
			mDraw = false;

			++mNum;
		}
	}

	
	if (mAButton == nullptr && SceneBase::mIsScene != SceneType::eGameClear)
	{
		mAButton = new AButtonUI();
	}
}