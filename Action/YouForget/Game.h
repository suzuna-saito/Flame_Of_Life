#pragma once

/*
* ゲームの進行を行うクラス
*/
class Game
{
public:
	// コンストラクタ
	Game();
	// デストラクタ
	~Game() {};

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <returns>true : 成功, false : 失敗</returns>
	bool Initialize();
	
	/// <summary>
	/// 終了処理
	/// </summary>
	void Termination();

	/// <summary>
	/// ゲームループ
	/// </summary>
	void GameLoop();
private:
	/// <summary>
	/// 入力関連の処理
	/// </summary>
	void ProcessInput();

	/// <summary>
	/// ゲームの更新処理
	/// </summary>
	void UpdateGame();

	/// <summary>
	/// 描画関連の処理
	/// </summary>
	virtual void GenerateOutput();

	/// <summary>
	/// ロードしたデータの解放
	/// </summary>
	void UnloadData();

	class SceneBase* mNowScene;			// 現在のシーン
	class FPS* mFps;					// FPS計測クラス
	class InputSystem* mInputSystem;	// 入力管理クラス
	
	bool mRunningFlag;					// ゲームを続けるかどうか(true:続ける)

	const float MWidth;					// 画面の横幅
	const float MHeight;				// 画面の縦幅

public:// ゲッターセッター

	/*
	@fn		最初のシーンを決める関数
	@param	_firstScene 最初のシーン
	*/
	void SetFirstScene(SceneBase* _firstScene);
};

