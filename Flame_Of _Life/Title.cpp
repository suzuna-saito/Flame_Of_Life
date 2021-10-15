/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_nowScene ���݂̃V�[��
*/
Title::Title(const Scene& _nowScene)
	:SceneBase()
{
	// ���C�g��ݒ�(�ݒ肵�Ȃ��Ɖ����f��Ȃ�)
	RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(1.0f, 0.7f, -0.7f);
	dir.m_diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.m_specColor = Vector3(0.8f, 0.8f, 0.8f);

	SetScene(_nowScene);

	// �^�C�g���摜
	mSprite = new Sprite("Assets/UI/Title.png");

}

/*
@fn	�f�X�g���N�^
*/
Title::~Title()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(title);
	delete mSprite;
}

void Title::Input(const InputState& _state)
{
	if (_state.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_START) == 1 ||
		_state.m_keyboard.GetKeyValue(SDL_SCANCODE_SPACE) == 1)
	{
		mGameSceneFlag = true;
	}
}

/*
@fn	���݂̃V�[�����ɖ��t���[���X�V����������
*/
SceneBase* Title::update()
{

	if (mGameSceneFlag)
	{
		return new Tutorial(tutorial);
	}

	return this;
}