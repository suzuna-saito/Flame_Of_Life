#pragma once

class Jump
{
public:
	// �R���X�g���N�^
	Jump();
	// �f�X�g���N�^
	~Jump();

	void Update();

private:
	// �W�����v�̏����x
	float mJumpSpeed;

	// �W�����v�̉����x
	float mJumpAccel;
};