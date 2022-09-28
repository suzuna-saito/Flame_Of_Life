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

	// ���݂̃t���[���ɂ�����������
	mDeltaTime = (SDL_GetTicks() - mBeforetickCount) / 1000.0f;
	// mDeltaTime�̒l���傫���Ȃ肷���Ȃ��悤�ɐ���
	if (mDeltaTime >= 0.10f)
	{
		mDeltaTime = 0.10f;
	}

	// �O�t���[���ɂ�����������
	mBeforetickCount = SDL_GetTicks();
}

void FPS::Wait()
{
	//�o�ߎ��Ԃ��r����1�t���[���ɂ����鎞�Ԃ��z���܂ő҂�
	/*
	 SDL_GetTicks()(SDL������������Ă���o�߂�������)��
	 mBeforetickCount + MOneFrameTickCount(�O�t���[���ɂ�����������+1�t���[���ɂ����鎞��)��
	 ������ΐ^��Ԃ��B
	*/
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mBeforetickCount + MOneFrameTickCount));
}
