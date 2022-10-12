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
	//// �V�[����eLastResult�ŃN���A�t���O�������Ă���������
	//if (mIsSceneType == SceneType::eLastResult && ResultBase::mClearEndFlag)
	//{
	//	// �����t�F�[�h�C����������
	//	mFade->SetFade(Color::White, Fade::FadeType::eIn);
	//}
	//else
	//{
	//	// �����t�F�[�h�C����������
	//	mFade->SetFade(Color::Black, Fade::FadeType::eIn);
	//}
}