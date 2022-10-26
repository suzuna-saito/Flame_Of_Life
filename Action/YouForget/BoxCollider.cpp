#include "pch.h"

BoxCollider::BoxCollider(GameObject* _owner, const GameObject::ObjTag _tag, OnCollisionFunc _func, int _updateOrder, int _collisionOrder)
	: ColliderComponent(_owner, _tag, _updateOrder, _collisionOrder)
	, mObjectBox(Vector3::Zero, Vector3::Zero)
	, mWorldBox(Vector3::Zero, Vector3::Zero)
	, mShouldRotate(true)
{
	PHYSICS->AddBox(this, _func);
}

/*
@fn		�f�X�g���N�^
*/
BoxCollider::~BoxCollider()
{
	PHYSICS->RemoveBox(this);
}

/*
@fn		Transform�̃��[���h�ϊ�
*/
void BoxCollider::OnUpdateWorldTransform()
{
	Refresh();
	PHYSICS->HitCheck(this);
}

/*
@fn		�q�b�g�����I�u�W�F�N�g����ȏ゠�����ꍇ�A�ǂ̃I�u�W�F�N�g�Ɖ����߂������邩
		�^�O�Œ��ׂ���ɂ܂�Transform�̃��[���h�ϊ�������
@brief	�q�b�g�����I�u�W�F�N�g��̊Ԃɂ����ꍇ�A��������������A���蔲������̂�
		�����h�����߂ɂ�����xTransform�̃��[���h�ϊ�������
*/
void BoxCollider::Refresh()
{
	mWorldBox = mObjectBox;

	mWorldBox.m_min = (mObjectBox.m_min * mOwner->GetScale().x);
	mWorldBox.m_max = (mObjectBox.m_max * mOwner->GetScale().x);

	if (mShouldRotate)
	{
		mWorldBox.Rotate(mOwner->GetRotation());
	}

	mWorldBox.m_min += mOwner->GetPosition();
	mWorldBox.m_max += mOwner->GetPosition();
}

