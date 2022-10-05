/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_nowScene ���݂̃V�[��
*/
Title::Title(const SceneType& _nowScene)
	:SceneBase()
{
	mIsScene = _nowScene;

	// �^�C�g���摜
	mFullPicture = new FullPicture("Assets/UI/Title/TitleB.png");

	ResultBase::mTrueEndFlag = true;

	// �擾�����A�C�e���̒��Ƀf�[�^�������Ă����
	if (ItemBase::mGetNumber.size() != 0)
	{
		ItemBase::mGetNumber.clear();
	}
}

/*
@fn	�f�X�g���N�^
*/
Title::~Title()
{
	delete mFullPicture;
	GAME_OBJECT_MANAGER->RemoveGameObjects(SceneType::eTitle);
}

void Title::Input(const InputState& _state)
{
	if (_state.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_A) == 1 ||
		_state.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::Released)
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
		return new FirstStage(SceneType::eFirst);
		//return new Tutorial(Scene::tutorial);
		//return new SecondStage(Scene::second);
		//return new ThirdStage(Scene::third);
		//return new Result(Scene::result);
	}

	return this;
}