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
	float mJumpSpeed;
	// �W�����v�̉����x
	float mJumpAccel;
	// �ō��W�����v�n�_
	float mMaxJumpHeight;

	// �W�����v���J�n�����u�Ԃ��ǂ���
	bool mStartFlag;
	// �W�����v�����ǂ���
	bool mJumpNow;
	// �ō��n�_�܂ŒB�������ǂ���
	bool mMaxFlag;

	// �|�W�V����
	Vector3 mAddPos;

public:
	// �W�����v���Ă邩�ǂ����Z�b�g����
	void SetJumpFlag(bool _flag) { mJumpNow = _flag; }
	// �W�����v���Ă邩�ǂ�����Ԃ�
	bool GetJumpFlag() { return mJumpNow; }

	// �W�����v�ő������|�W�V����
	Vector3 GetAddPos() { return mAddPos; }
};