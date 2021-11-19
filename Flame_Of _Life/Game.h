/*
@file Game.h
@brief ゲームの進行を行う
*/

/*
@brief	プリプロセッサ
*/
#pragma once

class FPS;
class InputSystem;

class Game
{
public:

	/*
	@fn	コンストラクタ
	*/
	Game();

	/*
	@fn	デストラクタ
	*/
	~Game() {};

	/*
	@fn		初期化処理
	@return true : 成功, false : 失敗(bool型)
	*/
	bool Initialize();

	/*
	@fn	終了処理
	*/
	void Termination();

	/*
	@fn	ゲームループ
	*/
	void GameLoop();

	//シーンを切り替えるか
	bool mSceneFlag;

private:

	//現在のシーン
	SceneBase* mNowScene;

	/*
	@fn	入力関連の処理
	*/
	void ProcessInput();

	/*
	@fn	描画関連の処理
	*/
	virtual void GenerateOutput();

	/*
	@fn	ゲームの更新処理
	*/
	void UpdateGame();

	/*
	@fn	ロードしたデータの解放
	*/
	void UnloadData();

	//FPS計測クラス
	FPS* mFps;
	//入力管理クラス
	InputSystem* mInputSystem;
	//ゲームを続けるかどうか
	bool mRunningFlag;

	const float MWidth;
	const float MHeight;
public://ゲッターセッター

	/*
	@fn		最初のシーンを決める関数
	@param	_firstScene 最初のシーン
	*/
	void SetFirstScene(SceneBase* _firstScene);
};

