#include "pch.h"

// �ÓI�����o�ϐ�
bool GoalObj::mGoalFlag = false; // �S�[���������ǂ���

GoalObj::GoalObj(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::SceneType _sceneTag)
	: GameObject(_sceneTag, _objectTag)
{
	// �S�[���������ǂ����t���O��false�ɂ���
	mGoalFlag = false;

	//GameObject�����o�ϐ��̏�����
	mTag = _objectTag;   // �I�u�W�F�N�g�^�O
	SetScale(_size);     // �I�u�W�F�N�g�T�C�Y
	SetPosition(_pos);   // �I�u�W�F�N�g�̃|�W�V����

	// �G�t�F�N�g
	new GoalEffect(this);

	//�낤�����̓����蔻��
	mSelfBoxCollider = new BoxCollider(this, ColliderTag::candleTag, GetOnCollisionFunc());
	AABB box = { Vector3(-50.0f,-10.0f,-50.0f),Vector3(50.0f,10.0f,50.0f) };
	mSelfBoxCollider->SetObjectBox(box);
}

/*
@fn		�낤�����̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void GoalObj::UpdateGameObject(float _deltaTime)
{
}

/*
@fn		�낤�������q�b�g�������̏���
@param	_hitObject �q�b�g�����Ώۂ̃Q�[���I�u�W�F�N�g�̃A�h���X
*/
void GoalObj::OnCollision(const GameObject& _hitObject)
{
	// �S�[���������ǂ����t���O��true�ɂ���
	mGoalFlag = true;
}
