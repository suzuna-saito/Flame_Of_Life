/*
@brief	�v���v���Z�b�T
*/
#include "pch.h"

//���݂̃V�[���̏�����
SceneBase::SceneType SceneBase::mIsScene = SceneType::eInit;

/*
@fn	�R���X�g���N�^
*/
SceneBase::SceneBase(const SceneType& _sceneType)
	: mFullPicture(nullptr)
	, mMapCreate(nullptr)
	, mClearFlag(false)
	, mGameSceneFlag(false)
	, mReturnTitleFlag(false)
	, mNextSceneCount(0)
	, mThisSpriteAlpha(1.0f)
{
	// �V�[���^�C�v�̍X�V
	mIsScene = _sceneType;

	//����
	const Vector3 AmbientLight = Vector3(0.4f, 0.4f, 0.4f);

	// ���C�g��ݒ�(�ݒ肵�Ȃ��Ɖ����f��Ȃ�)
	RENDERER->SetAmbientLight(Vector3(0.8f, 0.8f, 0.8f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(0.0f, 0.0f, 0.0f);
	dir.m_diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	//dir.m_diffuseColor = Vector3(0.5f, 0.5f, 0.8f);
	dir.m_specColor = Vector3(0.8f, 0.8f, 0.8f);
}

void SceneBase::Input(const InputState& _state)
{
	// �^�C�g���V�[���ȊO�ŃR���g���[���[�̃X�^�[�g�{�^���A�܂��́AB�L�[�������ꂽ�u��
	if (mIsScene != SceneType::eTitle && _state.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_START) == 1 ||
		mIsScene != SceneType::eTitle && _state.m_keyboard.GetKeyState(SDL_SCANCODE_B) == ButtonState::Released)
	{
		// �^�C�g���J�ڃt���O��true�ɂ���
		mReturnTitleFlag = true;
	}
}
