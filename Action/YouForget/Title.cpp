#include "pch.h"

Title::Title(const SceneType& _nowScene)
	:SceneBase(_nowScene)
{
	// mClearEndFlag��true�ɂ���
	ResultBase::mClearEndFlag = true;

	// �^�C�g���摜�̐���
	mFullPicture = new FullPicture("Assets/UI/Title/TitleB.png");
	
	// mGetNumber����ɂ���
	ItemBase::mGetNumber.clear();
}

Title::~Title()
{
	// ���݂̃V�[���Ő��������I�u�W�F�N�g��S�č폜
	GAME_OBJECT_MANAGER->RemoveGameObjects(SceneType::eTitle);
}

void Title::Input(const InputState& _state)
{
	// �t�F�[�h�X�V������Ȃ��Ƃ�
	// �R���g���[���[��A�{�^���A�܂��́A�X�y�[�X�L�[�������ꂽ�u��
	if (!Fade::mFadeFlag && _state.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_A) == 1 ||
		!Fade::mFadeFlag && _state.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::Released)
	{

		// �V�[���J�ڃt���O��true�ɂ���
		mGameSceneFlag = true;
	}
}

SceneBase::SceneType Title::update()
{
	// mGameSceneFlag��true���A�t�F�[�h������Ȃ����
	if (mGameSceneFlag && !Fade::mFadeFlag)
	{
		// ���̃V�[���̃^�C�v��Ԃ�
		return SceneType::eFirst;
		//return new FirstResult(SceneType::eFirstResult);
		//return new Tutorial(Scene::tutorial);
		//return new SecondStage(Scene::second);
		//return new ThirdStage(Scene::third);
		//return new Result(Scene::result);
	}

	return mIsSceneType;
}