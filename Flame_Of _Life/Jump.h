#pragma once

class Jump
{
public:
	// �R���X�g���N�^
	Jump(Vector3& _pos);
	// �f�X�g���N�^
	~Jump();


private:
	// �W�����v�̏����x
	float mJumpSpeed;

	// �W�����v�̉����x
	float mJumpAccel;
};