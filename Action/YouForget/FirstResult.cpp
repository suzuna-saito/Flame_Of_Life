/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_nowScene ���݂̃V�[��
*/
FirstResult::FirstResult(const Scene& _nowScene)
	:ResultBase(_nowScene)
{
	// �}�b�v�������ăA�C�e���Ɛ����摜���֘A�t��	
	mItemDescription[ItemNum::one] = "Assets/UI/FarstThree.png";
	mItemDescription[ItemNum::two] = "Assets/UI/FarstTwo.png";
	mItemDescription[ItemNum::three] = "Assets/UI/FarstOne.png";

	// �ǂ̃A�C�e��������Ă��邩����
	mSearch();
}

/*
@fn	�f�X�g���N�^
*/
FirstResult::~FirstResult()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(Scene::firstResult);
}

void FirstResult::Input(const InputState& _state)
{
	if (_state.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == ButtonState::Released ||
		_state.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::Released)
	{
		mDrawUpdate();
	}
}


/*
@fn	���݂̃V�[�����ɖ��t���[���X�V����������
*/
SceneBase* FirstResult::update()
{
	mResultUpdate();

	if (mGameSceneFlag)
	{
		return new SecondStage(Scene::second);
	}

	return this;
}