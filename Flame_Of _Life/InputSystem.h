/*
@brief	プリプロセッサ
*/
#pragma once


/*
enum ButtonState
ボタンの状態を表す
*/
enum ButtonState
{
	//押されていない
	None,
	//押した
	Pressed,
	//離した
	Released,
	//押されている
	Held
};

/*
@file KeyboardState.h
@brief キーボードの入力管理クラス
*/
class KeyboardState
{
public:
	// InputSystemから容易に更新できるようにする
	friend class InputSystem;
private:

	//現在のキーボードの入力状態
	const Uint8* mCurrState;
	//１フレーム前のキーボードの入力状態
	Uint8 mPrevState[SDL_NUM_SCANCODES];

public://ゲッターセッター

	/*
	@fn		現在のキーの入力状態のみを取得する
	@param	_keyCode SDL_Scancodeのキーコード
	@return	true : 押されている , false : 押されていない(bool型)
	*/
	bool GetKeyValue(SDL_Scancode _keyCode) const;

	/*
	@fn		現在と1フレーム前の状態からButtonStateを返す
	@param	_keyCode SDL_Scancodeのキーコード
	@return	ButtonState型の現在の状態(bool型)
	*/
	ButtonState GetKeyState(SDL_Scancode _keyCode) const;

};

/*
@file MouseState.h
@brief マウスの入力管理クラス
*/
class MouseState
{
public:

	//InputSystemから容易に更新できるようにする
	friend class InputSystem;

private:

	//マウスのポジション
	Vector2 mMousePos;
	//スクロールホイールのスクロール量
	Vector2 mScrollWheel;
	// 現在のマウスの入力状態
	Uint32 mCurrButtons;
	//１フレーム前のマウスの入力状態
	Uint32 mPrevButtons;
	// 相対マウスモードかどうか
	bool mRelativeFlag;

public://ゲッターセッター

	/*
	@fn		相対マウスモードかどうかを取得する
	@return	true : 相対モード , false , 通常モード(bool型)
	*/
	bool IsRelative() const { return mRelativeFlag; }

	/*
	@fn		現在のマウスのポジションを取得する
	@return	Position(Vector2型)
	*/
	const Vector2& GetPosition() const { return mMousePos; }

	/*
	@fn		現在のマウスのスクロールホイールの状態を取得する
	@return	スクロール量(Vector2型)
	*/
	const Vector2& GetScrollWheel() const { return mScrollWheel; }

	/*
	@fn		現在の入力状態のみを取得する
	@param	_button SDL_BUTTON定数
	@return	true : 押されている , false : 押されていない(bool型)
	*/
	bool GetButtonValue(int _button) const;

	/*
	@fn		現在と1フレーム前の状態からButtonStateを返す
	@param	_button SDL_BUTTON定数
	@return	ButtonState型の現在の状態(enum型 ButtonState)
	*/
	ButtonState GetButtonState(int _button) const;
};

/*
@file ControllerState.h
@brief コントローラーの入力管理クラス
*/
class ControllerState
{
public:

	// InputSystemから容易に更新できるようにする
	friend class InputSystem;

private:

	//現在のボタンの入力状態
	Uint8 mCurrButtons[SDL_CONTROLLER_BUTTON_MAX];
	//１フレーム前のボタンの入力状態
	Uint8 mPrevButtons[SDL_CONTROLLER_BUTTON_MAX];

	//両スティックの情報
	float mAxisValues[SDL_CONTROLLER_AXIS_MAX];
	Vector2 mLAxis;

public://ゲッターセッター

	/*
	@fn		現在の入力状態のみを取得する
	@param	_button SDL_GameControllerButtonのボタンコード
	@return	true : 押されている , false : 押されていない(bool型)
	*/
	bool GetButtonValue(SDL_GameControllerButton _button) const;

	/*
	@fn		現在と1フレーム前の状態からButtonStateを返す
	@param	_button SDL_GameControllerButtonのボタンコード
	@return	ButtonState型の現在の状態(enum型 ButtonState)
	*/
	ButtonState GetButtonState(SDL_GameControllerButton _button) const;

	/*
	@fn		 スティックの入力を0~32767で返す
	@param _iAxis どのスティックのどの値を取得するか
		   (左スティックのXを取得...SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX)
	@return スティックの入力情報(float型)
	*/
	float GetAxisValue(const SDL_GameControllerAxis _iAxis) const;

	/*
	@fn		スティックの入力を0~1で返す
	@return スティックの入力情報(Vector2型)
	*/
	const Vector2& GetLAxisVec() const { return mLAxis; }

};

/*
@struct InputState
各入力機器の入力状態をまとめたラッパー構造体
*/
struct InputState
{
	KeyboardState m_keyboard;
	MouseState m_mouse;
	ControllerState m_controller;
};

/*
@file InputSystem.h
@brief 入力情報を管理
*/
class InputSystem
{
public:

	/*
	@fn		初期化処理
	@return true : 成功 , false : 失敗(bool型)
	*/
	bool Initialize();

	/*
	@fn	終了処理
	*/
	void Shutdown();

	/*
	@fn	Updateの準備をする（SDL_PollEventsの直前に呼ぶ）
	*/
	void PrepareForUpdate();

	/*
	@fn  フレーム毎の処理（SDL_PollEventsの直後に呼ぶ）
	*/
	void Update();

	/*
	@fn		SDLイベントをInputSystemに渡す
	@param	_event SDLイベント
	*/
	void ProcessEvent(union SDL_Event& _event);

private:

	/*
	@fn		入力された値（int）をフィルタリングする（範囲内に収めて-1.0~1.0にまとめる）
	@param	_input 入力された値（int）
	@return	フィルタリングされた値(float型)
	*/
	float Filter1D(int _input);

	/*
	@fn		入力された値（int）をフィルタリングする（範囲内に収めて0.0~1.0にまとめる）
	@param	_inputX 入力された値のx（int）
	@param	_inputY 入力された値のy（int）
	@return	フィルタリングされた値(Vector2型)
	*/
	Vector2 Filter2D(int _inputX, int _inputY);

	//各入力機器の入力状態をまとめたラッパー構造体
	InputState mState;
	//SDLでコントローラーを認識するためのクラスポインタ
	SDL_GameController* mController;
	//コントローラーが接続されたか
	static bool mControllerConnected;

public://ゲッターセッター

	/*
	@fn		現在の入力状態を取得する
	@return 各入力情報をまとめた構造体(struct InputState)
	*/
	const InputState& GetState() const { return mState; }

	/*
	@return コントローラーが接続されたか(bool型)
	*/
	static bool GetConnectedController() { return mControllerConnected; }

	/*
	@fn		マウスのモードを設定する
	@param	_value true : 相対モード , false : デフォルトモード
	*/
	void SetRelativeMouseMode(bool _value);
};
