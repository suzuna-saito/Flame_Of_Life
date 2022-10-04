/*
@brief	�v���v���Z�b�T
*/
#pragma once

/*
�t���[���ɂ����������Ԃ��v���������݂���N���X
*/
class FPS
{
public:
	// �R���X�g���N�^
	FPS();
	// �f�X�g���N�^
	~FPS() {};

	// �t���[�����̏���
	void Update();

private:
	// �o�ߎ��Ԃ��r����1�t���[���ɂ����鎞�Ԃ��z���܂ő҂�
	void Wait();

	const Uint32 MSetFps;				// �t���[�����[�g�̍ō��l
	const Uint32 MOneFrameTickCount;	// �P�t���[���ɂ����鎞��
	int mBeforetickCount;				// �O�̃t���[���̂�����������
	float mDeltaTime;					// ���݂̃t���[���̂�����������

public:// �Q�b�^�[�Z�b�^�[
	// ���݂̃t���[���ɂ����������ԁifloat�^�j
	float GetDeltaTime() const { return mDeltaTime; }
};

