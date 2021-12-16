#include "pch.h"

//�R���g���[���[���ڑ����ꂽ���̃t���O�̏�����
bool InputSystem::mControllerConnected = 0;

/*
@fn		���݂̃L�[�̓��͏�Ԃ݂̂��擾����
@param	_keyCode SDL_Scancode�̃L�[�R�[�h
@return	true : ������Ă��� , false : ������Ă��Ȃ�(bool�^)
*/
bool KeyboardState::GetKeyValue(SDL_Scancode _keyCode) const
{
	return mCurrState[_keyCode] == 1;
}

/*
@fn		���݂�1�t���[���O�̏�Ԃ���ButtonState��Ԃ�
@param	_keyCode SDL_Scancode�̃L�[�R�[�h
@return	ButtonState�^�̌��݂̏��(enum�^ ButtonState)
*/
ButtonState KeyboardState::GetKeyState(SDL_Scancode _keyCode) const
{
	if (mPrevState[_keyCode] == 0)
	{
		if (mCurrState[_keyCode] == 0)
		{
			return ButtonState::None;
		}
		else
		{
			return ButtonState::Pressed;
		}
	}
	else // Prev state must be 1
	{
		if (mCurrState[_keyCode] == 0)
		{
			return ButtonState::Released;
		}
		else
		{
			return ButtonState::Held;
		}
	}
}

/*
@fn		���݂̓��͏�Ԃ݂̂��擾����
@param	_button SDL_BUTTON�萔
@return	true : ������Ă��� , false : ������Ă��Ȃ�(bool�^)
*/
bool MouseState::GetButtonValue(int _button) const
{
	return (SDL_BUTTON(_button) & mCurrButtons) == 1;
}

/*
@fn		���݂�1�t���[���O�̏�Ԃ���ButtonState��Ԃ�
@param	_button SDL_BUTTON�萔
@return	ButtonState�^�̌��݂̏��(enum�^ ButtonState)
*/
ButtonState MouseState::GetButtonState(int _button) const
{
	int mask = SDL_BUTTON(_button);
	if ((mask & mPrevButtons) == 0)
	{
		if ((mask & mCurrButtons) == 0)
		{
			return ButtonState::None;
		}
		else
		{
			return ButtonState::Pressed;
		}
	}
	else
	{
		if ((mask & mCurrButtons) == 0)
		{
			return ButtonState::Released;
		}
		else
		{
			return ButtonState::Held;
		}
	}
}

/*
@brief	���݂̓��͏�Ԃ݂̂��擾����
@param	_button SDL_GameControllerButton�̃{�^���R�[�h
@return	true : ������Ă��� , false : ������Ă��Ȃ�(bool�^)
*/
bool ControllerState::GetButtonValue(SDL_GameControllerButton _button) const
{
	return mCurrButtons[_button] == 1;
}

/*
@brief	���݂�1�t���[���O�̏�Ԃ���ButtonState��Ԃ�
@param	_button SDL_GameControllerButton�̃{�^���R�[�h
@return	ButtonState�^�̌��݂̏��(enum�^ ButtonState)
*/
ButtonState ControllerState::GetButtonState(SDL_GameControllerButton _button) const
{
	if (mPrevButtons[_button] == 0)
	{
		if (mCurrButtons[_button] == 0)
		{
			return ButtonState::None;
		}
		else
		{
			return ButtonState::Pressed;
		}
	}
	else // Prev state must be 1
	{
		if (mCurrButtons[_button] == 0)
		{
			return ButtonState::Released;
		}
		else
		{
			return ButtonState::Held;
		}
	}
}

/*
@fn		�X�e�B�b�N�̓��͂�0~32767�ŕԂ�
@param	_iAxis �ǂ̃X�e�B�b�N�̂ǂ̒l���擾���邩
		(���X�e�B�b�N��X���擾...SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX)
@return �X�e�B�b�N�̓��͏��(float�^)
*/
float ControllerState::GetAxisValue(const SDL_GameControllerAxis _iAxis) const
{
	return mAxisValues[_iAxis];
}

/*
@fn		����������
@return true : ���� , false : ���s(bool�^)
*/
bool InputSystem::Initialize()
{
	//�L�[�{�[�h�̏���������
	//���̃L�[�{�[�h�̏�Ԃ����蓖�Ă�
	mState.m_keyboard.mCurrState = SDL_GetKeyboardState(NULL);
	//�P�t���[���O�̓��͏�Ԃ�����������
	memset(mState.m_keyboard.mPrevState, 0,
		SDL_NUM_SCANCODES);

	memset(mState.m_controller.mAxisValues, 0,
		sizeof(float) * SDL_CONTROLLER_AXIS_MAX);


	//���݂ƂP�t���[���O�̃}�E�X�̓��͏�Ԃ�����������
	mState.m_mouse.mCurrButtons = 0;
	mState.m_mouse.mPrevButtons = 0;

	// �p�b�h�̐ݒ�t�@�C�� gamecontrollerdb.txt �̓ǂݍ��݂Ɩ�肪�������̃`�F�b�N
	int iNumOfControllers = SDL_GameControllerAddMappingsFromFile("Assets/Config/GameControllerdb.txt");
	if (iNumOfControllers == -1)
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_INPUT, "Error loading database [%s]", SDL_GetError());
		return false;
	}

	//�R���g���[���[���J��
	mController = nullptr;
	mController = SDL_GameControllerOpen(0);
	if (mController != nullptr)
	{
		mControllerConnected = true;
	}
	if (SDL_IsGameController(0))
	{
		printf("Controller :: %s \n", SDL_GameControllerMapping(mController));
	}

	// �R���g���[���C�x���g�̖����i�����炩��t���[�����ɏ�Ԃ��擾���邽�߁j
	SDL_GameControllerEventState(SDL_IGNORE);

	return true;
}

/*
@fn	�I������
*/
void InputSystem::Shutdown()
{
	if (!mController)
	{
		SDL_GameControllerClose(mController);
	}
	mController = nullptr;
}

/*
@fn	Update�̏���������iSDL_PollEvents�̒��O�ɌĂԁj
*/
void InputSystem::PrepareForUpdate()
{
	//���݂̓��͏�Ԃ��P�t���[���O�̓��͏�ԂɃR�s�[����
	//�L�[�{�[�h
	memcpy(mState.m_keyboard.mPrevState,
		mState.m_keyboard.mCurrState,
		SDL_NUM_SCANCODES);

	//�}�E�X
	mState.m_mouse.mPrevButtons = mState.m_mouse.mCurrButtons;
	mState.m_mouse.mRelativeFlag = false;
	mState.m_mouse.mScrollWheel = Vector2::Zero;

	//�R���g���[���[
	memcpy(mState.m_controller.mPrevButtons,
		mState.m_controller.mCurrButtons,
		SDL_CONTROLLER_BUTTON_MAX);
}

/*
@fn	�t���[�����̏����iSDL_PollEvents�̒���ɌĂԁj
*/
void InputSystem::Update()
{
	//�}�E�X
	int x = 0, y = 0;
	if (mState.m_mouse.mRelativeFlag)
	{
		mState.m_mouse.mCurrButtons =
			SDL_GetRelativeMouseState(&x, &y);
	}
	else
	{
		mState.m_mouse.mCurrButtons =
			SDL_GetMouseState(&x, &y);
	}

	mState.m_mouse.mMousePos.x = static_cast<float>(x) - 1024.0f / 2;
	mState.m_mouse.mMousePos.y = 768.0f / 2 - static_cast<float>(y);

	//�R���g���[���[
	//�E�{�^��
	for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; i++)
	{
		mState.m_controller.mCurrButtons[i] =
			SDL_GameControllerGetButton(mController,
				SDL_GameControllerButton(i));
	}


	// �R���g���[���������ꍇ�� early exit����
	if (mController != NULL)
	{
		// �O�̃t���[���̃R���g���[���̏�Ԃ��R�s�[����
		memcpy(&mState.m_controller.mPrevButtons, &mState.m_controller.mCurrButtons, sizeof(Uint8) * SDL_CONTROLLER_BUTTON_MAX);

		// �R���g���[���̏�Ԃ��X�V����
		SDL_GameControllerUpdate();

		// ���݂̃R���g���[���̃{�^����Ԃ�ۑ�
		for (int b = 0; b < SDL_CONTROLLER_BUTTON_MAX; ++b)
		{
			mState.m_controller.mCurrButtons[b] = SDL_GameControllerGetButton(mController, (SDL_GameControllerButton)b);
		}

		// ���݂̃R���g���[���̎�����ۑ�
		for (int a = 0; a < SDL_CONTROLLER_AXIS_MAX; ++a)
		{
			mState.m_controller.mAxisValues[a] = SDL_GameControllerGetAxis(mController, (SDL_GameControllerAxis)a);
		}

		// LPAD���͂��x�N�g��������
		const float maxInput = 32767.0f;
		mState.m_controller.mLAxis.x = (float)mState.m_controller.mAxisValues[SDL_CONTROLLER_AXIS_LEFTX];
		mState.m_controller.mLAxis.y = (float)mState.m_controller.mAxisValues[SDL_CONTROLLER_AXIS_LEFTY];

		//printf("%f\n", (float)state.Controller.axisValues[SDL_CONTROLLER_AXIS_LEFTX]);
		//�X�e�B�b�N�̓��͂ɍŒ�l��݂���(�萔�ȉ��̓J�b�g)
		mState.m_controller.mLAxis.x = (fabs(mState.m_controller.mLAxis.x) < (float)7849) ? 0.0f : mState.m_controller.mLAxis.x / maxInput;
		mState.m_controller.mLAxis.y = (fabs(mState.m_controller.mLAxis.y) < (float)8689) ? 0.0f : mState.m_controller.mLAxis.y / maxInput;

	}
}

/*
@fn		SDL�C�x���g��InputSystem�ɓn��
@param	_event SDL�C�x���g
*/
void InputSystem::ProcessEvent(SDL_Event& _event)
{
	switch (_event.type)
	{
	case SDL_MOUSEWHEEL:
		mState.m_mouse.mScrollWheel = Vector2(
			static_cast<float>(_event.wheel.x),
			static_cast<float>(_event.wheel.y));
		break;
	default:
		break;
	}
}

/*
@fn		�}�E�X�̃��[�h��ݒ肷��
@param	_value true : ���΃��[�h , false : �f�t�H���g���[�h
*/
void InputSystem::SetRelativeMouseMode(bool _value)
{
	SDL_bool set = _value ? SDL_TRUE : SDL_FALSE;
	SDL_SetRelativeMouseMode(set);

	mState.m_mouse.mRelativeFlag = _value;
}

/*
@brief  ���͂��ꂽ�l�iint�j���t�B���^�����O����i�͈͓��Ɏ��߂�-1.0~1.0�ɂ܂Ƃ߂�j
@param	_input ���͂��ꂽ�l�iint�j
@return	�t�B���^�����O���ꂽ�l(float�^)
*/
float InputSystem::Filter1D(int _input)
{
	//�f�b�h�]�[���i���̒l��菬�����Ȃ�0.0�ɂ���j
	const int deadZone = 250;
	//�ő�l�i���̒l���傫���Ă�1.0�ɂ���j
	const int maxValue = 30000;

	float retVal = 0.0f;

	//���͒l�̐�Βl�����
	int absValue = _input > 0 ? _input : -_input;
	//���͒l���f�b�h�]�[����菬�����Ȃ�
	if (absValue > deadZone)
	{
		//�f�b�h�]�[���ƍő�l�̊Ԃ�1.0�ȉ��ɂȂ�悤�v�Z����
		retVal = static_cast<float>(absValue - deadZone) /
			(maxValue - deadZone);
		//���������̒l�Ɠ����ɂ���
		retVal = _input > 0 ? retVal : -1.0f * retVal;
		//-1.0~1.0�̊ԂɎ��߂�
		retVal = Math::Clamp(retVal, -1.0f, 1.0f);
	}

	return retVal;
}

/*
@brief  ���͂��ꂽ�l�iint�j���t�B���^�����O����i�͈͓��Ɏ��߂�0.0~1.0�ɂ܂Ƃ߂�j
@param	_inputX ���͂��ꂽ�l��x�iint�j
@param	_inputY ���͂��ꂽ�l��y�iint�j
@return	�t�B���^�����O���ꂽ�l(Vector2�^)
*/
Vector2 InputSystem::Filter2D(int _inputX, int _inputY)
{
	//�f�b�h�]�[���i���̒l��菬�����Ȃ�0.0�ɂ���j
	const float deadZone = 8000.0f;
	//�ő�l�i���̒l���傫���Ă�1.0�ɂ���j
	const float maxValue = 30000.0f;

	//2�����x�N�g���ɂ���
	Vector2 dir;
	dir.x = static_cast<float>(_inputX);
	dir.y = static_cast<float>(_inputY);

	float length = dir.Length();

	//���͒l�̃x�N�g���̒������f�b�h�]�[����菬�����Ȃ�
	if (length < deadZone)
	{
		dir = Vector2::Zero;
	}
	else
	{
		//�f�b�h�]�[���ƍő�l�̊Ԃ�1.0�ȉ��ɂȂ�悤�v�Z����
		float f = (length - deadZone) / (maxValue - deadZone);
		//0.0��1.0�̊ԂɎ��߂�
		f = Math::Clamp(f, 0.0f, 1.0f);
		//�x�N�g���𐳋K�����āA�����̒l�ɃX�P�[�����O����
		dir *= f / length;
	}

	return dir;
}
