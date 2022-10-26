/*
@file	SphereCollider.h
@brief	���̓����蔻����s���R���|�[�l���g
*/

/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_owner �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
@param	_tag �A�^�b�`����Q�[���I�u�W�F�N�g�̓����蔻��̃^�O
@param	_func ���̃I�u�W�F�N�g�Ɠ����������ɌĂ΂��֐��|�C���^(GetOnCollisionFunc���Ă�)
@param	_updateOrder �R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j
@param	_collisionOrder �����蔻�莞�ɁA�߂荞�݂��瓮���������̗D��x�����߂鐔�l
*/
SphereCollider::SphereCollider(GameObject* _owner, GameObject::ObjTag _tag, OnCollisionFunc _func, int _updateOrder, int _collisionOrder)
	: ColliderComponent(_owner, _tag, _updateOrder, _collisionOrder)
	, mObjectSphere(Vector3::Zero, 0.0f)
	, mWorldSphere(Vector3::Zero, 0.0f)
{
	PHYSICS->AddSphere(this, _func);
}

/*
@fn	�f�X�g���N�^
*/
SphereCollider::~SphereCollider()
{
	PHYSICS->RemoveSphere(this);
}

/*
@fn	Transform�̃��[���h�ϊ�
*/
void SphereCollider::OnUpdateWorldTransform()
{
	Refresh();
	PHYSICS->HitCheck(this);
}

/*
@fn		�q�b�g�����I�u�W�F�N�g����ȏ゠�����ꍇ�A�ǂ̃I�u�W�F�N�g�Ɖ����߂������邩
		�^�O�Œ��ׂ���ɂ܂�Transform�̃��[���h�ϊ�������
@detail �q�b�g�����I�u�W�F�N�g��̊Ԃɂ����ꍇ�A��������������A���蔲������̂�
		�����h�����߂ɂ�����xTransform�̃��[���h�ϊ�������
*/
void SphereCollider::Refresh()
{
	//���[���h���W�ł̒��S�ʒu���X�V����
	mWorldSphere.m_center = mObjectSphere.m_center + mOwner->GetPosition();
	//���[���h��Ԃł̋��̑傫�����X�V����
	mWorldSphere.m_radius = mObjectSphere.m_radius * mOwner->GetScale().x;
}