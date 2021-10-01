/*
@file	FPS.h
@brief	フレームにかかった時間を計測し上限を設けるクラス
*/

/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn	コンストラクタ
*/
FPS::FPS()
	: mSetFps(60)
	, mOneFrameTickCount(1000 / mSetFps)
	, mFpsCount(0)
	, mFrameStartTickTime(0)
	, mFps(0)
	, mBeforetickCount(0)
	, mDeltaTime(0)
{

}

/*
@fn	デストラクタ
*/
FPS::~FPS()
{
}

/*
@fn	フレーム毎の処理
*/
void FPS::Update()
{
	Wait();
	mDeltaTime = (SDL_GetTicks() - mBeforetickCount) / 1000.0f;
	if (mDeltaTime >= 0.10f)
	{
		mDeltaTime = 0.10f;
	}
	mBeforetickCount = SDL_GetTicks();
	//1フレーム目の時刻を保存
	if (mFpsCount == 0)
	{
		mFrameStartTickTime = SDL_GetTicks();
	}
	//設定したフレーム数が経過したら
	if (mFpsCount == mSetFps)
	{
		int nowTickTime = SDL_GetTicks();
		mFps = 1000 / ((nowTickTime - mFrameStartTickTime) / mSetFps);
		mFpsCount = 0;
	}
	else
	{
		mFpsCount++;
	}
}

/*
@fn	FPSが設定値より大きくならないための制御
*/
void FPS::Wait()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mBeforetickCount + mOneFrameTickCount));
}
