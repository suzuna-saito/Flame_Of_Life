#include "pch.h"

int main(int argc, char** argv)
{
	// ゲームクラスの定義
	Game game;
	// ゲームクラスの初期化が成功したら
	if (game.Initialize())
	{
		// 最初のシーンを生成
		game.SetNewScene(SceneBase::SceneType::eFirst);
		// ゲームループに入る
		game.GameLoop();
	}

	//ゲームクラスの終了処理
	game.Termination();

	return 0;
}