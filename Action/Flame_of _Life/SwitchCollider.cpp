#include "pch.h"

// �R���X�g���N�^
SwitchCollider::SwitchCollider(Switch* _owner,const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	:GameObject(_sceneTag, _objectTag)
	, mOwner(_owner)
{
	SetPosition(_owner->GetPosition());

	mTag = Tag::SwitchCenter;

	//�X�C�b�`���S�̓����蔻��(�{�b�N�X)
	mSwitchBoxCollider = new BoxCollider(_owner, ColliderTag::switchTag, GetOnCollisionFunc());
	AABB Switchbox = { Vector3(2.0f,-4.0f,15.0f),Vector3(-2.0f,4.0f,16.0f) };
	mSwitchBoxCollider->SetObjectBox(Switchbox);
}

void SwitchCollider::UpdateGameObject(float _deltaTime)
{
	// �X�C�b�`�̃t���O��false�ɖ߂�
	Switch::mSwitchFlag = false;
}

void SwitchCollider::OnCollision(const GameObject& _hitObject)
{
	//�q�b�g�����I�u�W�F�N�g�̃^�O���擾
	mTag = _hitObject.GetTag();

	// �X�C�b�`�Ɠ������������A�X�C�b�`�t���O��false�̎�
	if (mTag == Tag::Switch && !Switch::mSwitchFlag)
	{
		// �t���O��true�ɂ���
		Switch::mSwitchFlag = true;
	}
}
