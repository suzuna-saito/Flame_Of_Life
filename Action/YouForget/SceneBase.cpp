#include "pch.h"

// �ÓI�����o�ϐ��̏�����
SceneBase::SceneType SceneBase::mIsSceneType = SceneType::eInit;	// ���݂̃V�[���^�C�v

SceneBase::SceneBase(const SceneType& _sceneType)
	: mFade(nullptr)
	, mFullPicture(nullptr)
	, mMapCreate(nullptr)
	, mGameSceneFlag(false)
	, mReturnTitleFlag(false)
{
	// �V�[���^�C�v�̍X�V
	mIsSceneType = _sceneType;

	// ���C�g��ݒ�(�ݒ肵�Ȃ��Ɖ����f��Ȃ�)
	RENDERER->SetAmbientLight(Vector3(1.0f, 1.0f, 1.0f));	// ���̐F
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3::Zero;						// ����
	dir.m_diffuseColor = Vector3(1.0f, 1.0f, 1.0f);			// �g�U���ːF
	dir.m_specColor = Vector3(1.0f, 1.0f, 1.0f);			// ���ʔ��ːF
}