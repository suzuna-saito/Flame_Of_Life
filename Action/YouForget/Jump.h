#pragma once

class Jump:public Component
{
public:
	// �R���X�g���N�^
	Jump(GameObject* _owner);
	// �f�X�g���N�^
	~Jump();

	// �X�V����
	void Update(float _deltaTime)override;

private:
	// �W�����v�̏����x
	float MJumpSpeed;
	// �W�����v�̉����x
	float MJumpAccel;
	
	// �W�����v���J�n�����u�Ԃ��ǂ���
	bool mStartFlag;
	// �W�����v�����ǂ���
	bool mJumpNow;
	// �W�����v���I�����邩�ǂ���
	bool mEndFlag;

	// �|�W�V����
	float mVelocity;
public:
	// �W�����v���Ă邩�ǂ����Z�b�g����
	void SetJumpStart(bool _flag) { mStartFlag = _flag; }

	// �W�����v�I�����邩�ǂ����Z�b�g����
	void SetEndJump(bool _flag) { mEndFlag = _flag; }

	// �W�����v���Ă邩�ǂ�����Ԃ�
	const bool GetJumpStartFlag() const { return mStartFlag; }
	const bool GetJumpFlag() const { return mJumpNow; }

	// �W�����v�ő�����Z���̑�����
	const float GetVelocity() const { return mVelocity; }
};