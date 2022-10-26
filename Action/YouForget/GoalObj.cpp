#include "pch.h"

// �ÓI�����o�ϐ��̏�����
bool GoalObj::mGoalFlag = false; // �S�[���������ǂ���

GoalObj::GoalObj(const Vector3 _pos)
	: GameObject(ObjTag::eGoal)
{
	// �����������ɃS�[���������ǂ����t���O��false�ɂ���
	mGoalFlag = false;

	// �S�[���̓����蔻���ݒ�
	mSelfBoxCollider = new BoxCollider(this, mTag, GetOnCollisionFunc());
	AABB box = { Vector3(-50.0f,-10.0f,-50.0f),Vector3(50.0f,10.0f,50.0f) };
	mSelfBoxCollider->SetObjectBox(box);

	// GameObject�����o�ϐ��̏�����
	SetScale(Vector3(6.0f,6.0f,6.0f));	// �I�u�W�F�N�g�T�C�Y
	SetPosition(_pos);					// �I�u�W�F�N�g�̃|�W�V����

	// �S�[���G�t�F�N�g�̐���
	new GoalEffect(this);
}

void GoalObj::OnCollision(const GameObject& _hitObject)
{
	// �v���C���[���s���\�Ȏ��v���C���[���S�[���ɓ���������
	if (Player::mOperable)
	{
		// �S�[���������ǂ����t���O��true�ɂ���
		mGoalFlag = true;
	}
}
