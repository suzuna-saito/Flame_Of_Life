#include "pch.h"

FPS::FPS()
	: MSetFps(60)
	, MOneFrameTickCount(1000 / MSetFps)
	, mBeforetickCount(0)
	, mDeltaTime(0)
{
}

void FPS::Update()
{
	Wait();

	// 現在のフレームにかかった時間
	mDeltaTime = (SDL_GetTicks() - mBeforetickCount) / 1000.0f;
	// mDeltaTimeの値が大きくなりすぎないように制御
	if (mDeltaTime >= 0.10f)
	{
		mDeltaTime = 0.10f;
	}

	// 前フレームにかかった時間
	mBeforetickCount = SDL_GetTicks();
}

void FPS::Wait()
{
	//経過時間を比較して1フレームにかける時間を越すまで待つ
	/*
	 SDL_GetTicks()(SDLが初期化されてから経過した時間)が
	 mBeforetickCount + MOneFrameTickCount(前フレームにかかった時間+1フレームにかける時間)を
	 超えれば真を返す。
	*/
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mBeforetickCount + MOneFrameTickCount));
}
