#include "pch.h"

Title::Title(const SceneType& _nowScene)
	:SceneBase(_nowScene)
{
	// mClearEndFlag��true�ɂ���
	ResultBase::mClearEndFlag = true;
	// �擾�����s�[�X�̏�Ԃ���ɂ���
	PuzzlePiece::mGetNumber.clear();

	// �^�C�g���摜�̐���
	mFullPicture = new FullPicture("Assets/UI/Title/Title.png");
}

Title::~Title()
{
	// ���݂̃V�[���Ő��������I�u�W�F�N�g��S�č폜
	GAME_OBJECT_MANAGER->RemoveGameObjects(SceneType::eTitle);
}

void Title::Input(const InputState& _state)
{
	// �R���g���[���[��A�{�^���A�܂��́A�X�y�[�X�L�[�������ꂽ�u��
	if (_state.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_A) == 1 ||
		_state.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::Released)
	{
		// �V�[���J�ڃt���O��true�ɂ���
		mGameSceneFlag = true;
		// �����t�F�[�h�A�E�g��������
		mFade->SetFade(Color::Black, Fade::FadeType::eOut);
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
		//return SceneType::eThirdResult;
		//return new Result(Scene::result);
	}

	return mIsSceneType;
}