/*
@brief	�v���v���Z�b�T
*/
#pragma once


/*
enum ButtonState
�{�^���̏�Ԃ�\��
*/
enum ButtonState
{
	//������Ă��Ȃ�
	None,
	//������
	Pressed,
	//������
	Released,
	//������Ă���
	Held
};

/*
@file KeyboardState.h
@brief �L�[�{�[�h�̓��͊Ǘ��N���X
*/
class KeyboardState
{
public:
	// InputSystem����e�ՂɍX�V�ł���悤�ɂ���
	friend class InputSystem;
private:

	//���݂̃L�[�{�[�h�̓��͏��
	const Uint8* mCurrState;
	//�P�t���[���O�̃L�[�{�[�h�̓��͏��
	Uint8 mPrevState[SDL_NUM_SCANCODES];

public://�Q�b�^�[�Z�b�^�[

	/*
	@fn		���݂̃L�[�̓��͏�Ԃ݂̂��擾����
	@param	_keyCode SDL_Scancode�̃L�[�R�[�h
	@return	true : ������Ă��� , false : ������Ă��Ȃ�(bool�^)
	*/
	bool GetKeyValue(SDL_Scancode _keyCode) const;

	/*
	@fn		���݂�1�t���[���O�̏�Ԃ���ButtonState��Ԃ�
	@param	_keyCode SDL_Scancode�̃L�[�R�[�h
	@return	ButtonState�^�̌��݂̏��(bool�^)
	*/
	ButtonState GetKeyState(SDL_Scancode _keyCode) const;

};

/*
@file MouseState.h
@brief �}�E�X�̓��͊Ǘ��N���X
*/
class MouseState
{
public:

	//InputSystem����e�ՂɍX�V�ł���悤�ɂ���
	friend class InputSystem;

private:

	//�}�E�X�̃|�W�V����
	Vector2 mMousePos;
	//�X�N���[���z�C�[���̃X�N���[����
	Vector2 mScrollWheel;
	// ���݂̃}�E�X�̓��͏��
	Uint32 mCurrButtons;
	//�P�t���[���O�̃}�E�X�̓��͏��
	Uint32 mPrevButtons;
	// ���΃}�E�X���[�h���ǂ���
	bool mRelativeFlag;

public://�Q�b�^�[�Z�b�^�[

	/*
	@fn		���΃}�E�X���[�h���ǂ������擾����
	@return	true : ���΃��[�h , false , �ʏ탂�[�h(bool�^)
	*/
	bool IsRelative() const { return mRelativeFlag; }

	/*
	@fn		���݂̃}�E�X�̃|�W�V�������擾����
	@return	Position(Vector2�^)
	*/
	const Vector2& GetPosition() const { return mMousePos; }

	/*
	@fn		���݂̃}�E�X�̃X�N���[���z�C�[���̏�Ԃ��擾����
	@return	�X�N���[����(Vector2�^)
	*/
	const Vector2& GetScrollWheel() const { return mScrollWheel; }

	/*
	@fn		���݂̓��͏�Ԃ݂̂��擾����
	@param	_button SDL_BUTTON�萔
	@return	true : ������Ă��� , false : ������Ă��Ȃ�(bool�^)
	*/
	bool GetButtonValue(int _button) const;

	/*
	@fn		���݂�1�t���[���O�̏�Ԃ���ButtonState��Ԃ�
	@param	_button SDL_BUTTON�萔
	@return	ButtonState�^�̌��݂̏��(enum�^ ButtonState)
	*/
	ButtonState GetButtonState(int _button) const;
};

/*
@file ControllerState.h
@brief �R���g���[���[�̓��͊Ǘ��N���X
*/
class ControllerState
{
public:

	// InputSystem����e�ՂɍX�V�ł���悤�ɂ���
	friend class InputSystem;

private:

	//���݂̃{�^���̓��͏��
	Uint8 mCurrButtons[SDL_CONTROLLER_BUTTON_MAX];
	//�P�t���[���O�̃{�^���̓��͏��
	Uint8 mPrevButtons[SDL_CONTROLLER_BUTTON_MAX];

	//���X�e�B�b�N�̏��
	float mAxisValues[SDL_CONTROLLER_AXIS_MAX];
	Vector2 mLAxis;

public://�Q�b�^�[�Z�b�^�[

	/*
	@fn		���݂̓��͏�Ԃ݂̂��擾����
	@param	_button SDL_GameControllerButton�̃{�^���R�[�h
	@return	true : ������Ă��� , false : ������Ă��Ȃ�(bool�^)
	*/
	bool GetButtonValue(SDL_GameControllerButton _button) const;

	/*
	@fn		���݂�1�t���[���O�̏�Ԃ���ButtonState��Ԃ�
	@param	_button SDL_GameControllerButton�̃{�^���R�[�h
	@return	ButtonState�^�̌��݂̏��(enum�^ ButtonState)
	*/
	ButtonState GetButtonState(SDL_GameControllerButton _button) const;

	/*
	@fn		 �X�e�B�b�N�̓��͂�0~32767�ŕԂ�
	@param _iAxis �ǂ̃X�e�B�b�N�̂ǂ̒l���擾���邩
		   (���X�e�B�b�N��X���擾...SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX)
	@return �X�e�B�b�N�̓��͏��(float�^)
	*/
	float GetAxisValue(const SDL_GameControllerAxis _iAxis) const;

	/*
	@fn		�X�e�B�b�N�̓��͂�0~1�ŕԂ�
	@return �X�e�B�b�N�̓��͏��(Vector2�^)
	*/
	const Vector2& GetLAxisVec() const { return mLAxis; }

};

/*
@struct InputState
�e���͋@��̓��͏�Ԃ��܂Ƃ߂����b�p�[�\����
*/
struct InputState
{
	KeyboardState m_keyboard;
	MouseState m_mouse;
	ControllerState m_controller;
};

/*
@file InputSystem.h
@brief ���͏����Ǘ�
*/
class InputSystem
{
public:

	/*
	@fn		����������
	@return true : ���� , false : ���s(bool�^)
	*/
	bool Initialize();

	/*
	@fn	�I������
	*/
	void Shutdown();

	/*
	@fn	Update�̏���������iSDL_PollEvents�̒��O�ɌĂԁj
	*/
	void PrepareForUpdate();

	/*
	@fn  �t���[�����̏����iSDL_PollEvents�̒���ɌĂԁj
	*/
	void Update();

	/*
	@fn		SDL�C�x���g��InputSystem�ɓn��
	@param	_event SDL�C�x���g
	*/
	void ProcessEvent(union SDL_Event& _event);

private:

	/*
	@fn		���͂��ꂽ�l�iint�j���t�B���^�����O����i�͈͓��Ɏ��߂�-1.0~1.0�ɂ܂Ƃ߂�j
	@param	_input ���͂��ꂽ�l�iint�j
	@return	�t�B���^�����O���ꂽ�l(float�^)
	*/
	float Filter1D(int _input);

	/*
	@fn		���͂��ꂽ�l�iint�j���t�B���^�����O����i�͈͓��Ɏ��߂�0.0~1.0�ɂ܂Ƃ߂�j
	@param	_inputX ���͂��ꂽ�l��x�iint�j
	@param	_inputY ���͂��ꂽ�l��y�iint�j
	@return	�t�B���^�����O���ꂽ�l(Vector2�^)
	*/
	Vector2 Filter2D(int _inputX, int _inputY);

	//�e���͋@��̓��͏�Ԃ��܂Ƃ߂����b�p�[�\����
	InputState mState;
	//SDL�ŃR���g���[���[��F�����邽�߂̃N���X�|�C���^
	SDL_GameController* mController;
	//�R���g���[���[���ڑ����ꂽ��
	static bool mControllerConnected;

public://�Q�b�^�[�Z�b�^�[

	/*
	@fn		���݂̓��͏�Ԃ��擾����
	@return �e���͏����܂Ƃ߂��\����(struct InputState)
	*/
	const InputState& GetState() const { return mState; }

	/*
	@return �R���g���[���[���ڑ����ꂽ��(bool�^)
	*/
	static bool GetConnectedController() { return mControllerConnected; }

	/*
	@fn		�}�E�X�̃��[�h��ݒ肷��
	@param	_value true : ���΃��[�h , false : �f�t�H���g���[�h
	*/
	void SetRelativeMouseMode(bool _value);
};
