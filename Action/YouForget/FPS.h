/*
@brief	プリプロセッサ
*/
#pragma once

/*
フレームにかかった時間を計測し上限を設けるクラス
*/
class FPS
{
public:
	// コンストラクタ
	FPS();
	// デストラクタ
	~FPS() {};

	// フレーム毎の処理
	void Update();

private:
	// 経過時間を比較して1フレームにかける時間を越すまで待つ
	void Wait();

	// フレームレートの最高値
	const Uint32 MSetFps;
	// １フレームにかける時間
	const Uint32 MOneFrameTickCount;
	// 前のフレームのかかった時間
	int mBeforetickCount;
	// 現在のフレームのかかった時間
	float mDeltaTime;

public:// ゲッターセッター
	// 現在のフレームにかかった時間（float型）
	float GetDeltaTime() const { return mDeltaTime; }
};

