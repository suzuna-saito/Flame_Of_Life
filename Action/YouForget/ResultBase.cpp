/*
@brief	�C���N���[�h
*/
#include "pch.h"

bool ResultBase::mTrueEndFlag = true;
//Sprite* ResultBase::mEndSprite;

/*
@fn		�R���X�g���N�^
@param	_nowScene ���݂̃V�[��
*/
ResultBase::ResultBase(const SceneType& _nowScene)
	:SceneBase()
	, mDescription()
	, mDeleteDescription()
	, mDraw(false)
	, mNowDescription(nullptr)
	, mButtonSprite(nullptr)
	, mNum(0)
{
	SetScene(_nowScene);

	/*if (GetScene() == Scene::gameClear)
	{
		if (mTrueEndFlag)
		{
			mSprite = new Sprite("Assets/UI/EndResult/Clear_1.png");
		}
		else
		{
			mSprite = new Sprite("Assets/UI/EndResult/Clear_4.png");
		}
	}*/
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

	delete mButtonSprite;
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

	// �S�Ẵs�[�X������ł��ĂȂ�������
	if (GetScene() != SceneType::eGameClear &&
		mDescription.size() != 3)
	{
		mDescription.push_back("Assets/UI/ResultBase/BadWord.png");
		mTrueEndFlag = false;
	}
	else
	{
		// �V�[���ɂ���čX�ɉ摜��ǉ�
		switch (GetScene())
		{
		case SceneType::eFirstResult:
			mDescription.push_back("Assets/UI/FirstResult/Word_1.png");
			mDescription.push_back("Assets/UI/FirstResult/Word_2.png");
			break;
		case SceneType::eSecondResult:
			mDescription.push_back("Assets/UI/SecondResult/Word_1.png");
			mDescription.push_back("Assets/UI/SecondResult/Word_2.png");
			break;
		case SceneType::eThirdResult:
			mDescription.push_back("Assets/UI/ThirdResult/Word_1.png");
			mDescription.push_back("Assets/UI/ThirdResult/Word_2.png");
			break;
		case SceneType::eGameClear:
			if (mTrueEndFlag)
			{
				mDescription.push_back("Assets/UI/EndResult/Clear_2.png");
				mDescription.push_back("Assets/UI/EndResult/Clear_3.png");
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

	if (GetScene() == SceneType::eGameClear)
	{
		if (GetScene() == SceneType::eGameClear && mSprite != nullptr)
		{
			mSprite->SetThisVisible(false);
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
		if (mNum == mDescription.size())
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
			mNowDescription = new Sprite(mDescription[mNum]);
			// ��xnew������AmDraw��false�ɂ���B
			mDraw = false;

			++mNum;

			// �f�X�g���N�^�ō폜����悤��vector�ɕۑ����Ă���
			mDeleteDescription.push_back(mNowDescription);
		}
	}

	
	if (mButtonSprite == nullptr && GetScene() != SceneType::eGameClear)
	{
		mButtonSprite = new Sprite("Assets/UI/ResultBase/Button.png");
	}
}

