/*
@file	FPS.h
@brief	�t���[���ɂ����������Ԃ��v���������݂���N���X
*/

/*
@brief	�v���v���Z�b�T
*/
#pragma once

class FPS
{
public:

	/*
	@fn	�R���X�g���N�^
	*/
	FPS();

	/*
	@fn	�f�X�g���N�^
	*/
	~FPS();

	/*
	@fn	�t���[�����̏���
	*/
	void Update();
private:
	/*
	@fn	FPS���ݒ�l���傫���Ȃ�Ȃ����߂̐���
	*/
	void Wait();

	//�t���[�����[�g�̍ō��l
	const Uint32 mSetFps;
	//�P�t���[���ɂ����鎞��
	const Uint32 mOneFrameTickCount;
	//�t���[���̃J�E���^�[
	Uint32 mFpsCount;
	//FPS�̌v�Z���n�߂����̎���
	Uint32 mFrameStartTickTime;
	//�v�Z�����t���[�����[�g
	Uint32 mFps;
	//�O�̃t���[���̂�����������
	int mBeforetickCount;
	//���݂̃t���[���̂�����������
	float mDeltaTime;
public://�Q�b�^�[�Z�b�^�[
	/*
	@return ���݂̃t���[���ɂ�����������(float�^)
	*/
	float GetDeltaTime() { return mDeltaTime; }
};

