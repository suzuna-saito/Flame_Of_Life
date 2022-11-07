#include "pch.h"

// �ÓI�����o�ϐ��̏�����
SceneBase::SceneType SceneBase::mIsSceneType = SceneType::eInit;	// ���݂̃V�[���^�C�v

SceneBase::SceneBase(const SceneType& _sceneType)
	: mFullPicture(nullptr)
	, mMapCreate(nullptr)
	, mGameSceneFlag(false)
	, mReturnTitleFlag(false)
{
	// ���C�g��ݒ�(�ݒ肵�Ȃ��Ɖ����f��Ȃ�)
	RENDERER->SetAmbientLight(Vector3(1.0f, 1.0f, 1.0f));	// ���̐F
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3::Zero;						// ����
	dir.m_diffuseColor = Vector3(1.0f, 1.0f, 1.0f);			// �g�U���ːF
	dir.m_specColor = Vector3(1.0f, 1.0f, 1.0f);			// ���ʔ��ːF

	// �V�[���^�C�v�̍X�V
	mIsSceneType = _sceneType;

	// �w�iUI�̐ݒ�
	SetBackUI();
	// �t�F�[�h�C���̐ݒ�
	SetFadein();
}

void SceneBase::SetBackUI()
{
	// �I�u�W�F�N�g�̉��ɕ`�悵�Ă���摜
	mFullPicture = new FullPicture("Assets/UI/Back/Back.png", UIComponent::UIDrawType::eFar);

	//// �v���C�X�e�[�W��������
	//if (mIsSceneType == SceneType::eFirst || mIsSceneType == SceneType::eSecond || mIsSceneType == SceneType::eThird)
	//{
	//	// �w�i�摜����
	//	mFullPicture = new FullPicture("Assets/UI/Back/BackPuzzle7.png");
	//}
}

void SceneBase::SetFadein()
{
	// �t�F�[�h�N���X�̐���
	mFade = new Fade;

	// �V�[����eLastResult�ŃN���A�t���O�������Ă���������
	if (mIsSceneType == SceneType::eLastResult && ResultBase::mClearEndFlag)
	{
		// �����t�F�[�h�C����������
		mFade->SetFade(Color::White, Fade::FadeType::eIn);
	}
	else
	{
		// �����t�F�[�h�C����������
		mFade->SetFade(Color::Black, Fade::FadeType::eIn);
	}
}