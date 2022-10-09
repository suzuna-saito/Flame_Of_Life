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
	// ゲームループ
	void GameLoop();
	// 終了処理
	void Termination();

private:
	// 入力関連の処理
	void ProcessInput();
	// ゲームの更新処理
	void UpdateGame();
	// 描画関連の処理
	virtual void GenerateOutput();
	// ロードしたデータの解放
	void UnloadData();

	class SceneBase* mNowScene;				// 現在のシーン
	class FPS* mFps;						// FPS計測クラス
	class InputSystem* mInputSystem;		// 入力管理クラス
	
	SceneBase::SceneType mReturnSceneType;	// シーンの更新時に返ってきたシーンタイプ

	bool mRunningFlag;						// ゲームを続けるかどうか(true:続ける)

	const float MWidth;						// 画面の横幅
	const float MHeight;					// 画面の縦幅

public:// ゲッターセッター
	/// <summary>
	/// 新しいシーンを生成する
	/// </summary>
	/// <param name="_sceneType">生成したいシーンタイプ</param>
	void SetNewScene(const SceneBase::SceneType _sceneType);
};