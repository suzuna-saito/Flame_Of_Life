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

	const Uint32 MSetFps;				// フレームレートの最高値
	const Uint32 MOneFrameTickCount;	// １フレームにかける時間
	int mBeforetickCount;				// 前のフレームのかかった時間
	float mDeltaTime;					// 現在のフレームのかかった時間

public:// ゲッターセッター
	// 現在のフレームにかかった時間（float型）
	float GetDeltaTime() const { return mDeltaTime; }
};

