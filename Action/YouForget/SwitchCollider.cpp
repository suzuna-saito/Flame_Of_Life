#include "pch.h"

// �ÓI�����o�̏�����
Ground::GroundColor SwitchCollider::mLinkageColor = Ground::GroundColor::eRed;

// �R���X�g���N�^
SwitchCollider::SwitchCollider(Switch* _owner, const ObjTag& _objectTag, const SceneBase::SceneType _sceneTag, const Ground::GroundColor _switchColor)
	:GameObject(ObjTag::eSwitchCenter)
	, mOwner(_owner)
	, mSwitchColor(_switchColor)
{
	SetPosition(_owner->GetPosition());

	//�X�C�b�`���S�̓����蔻��(�{�b�N�X)
	mSwitchBoxCollider = new BoxCollider(this,mTag, GetOnCollisionFunc());
	AABB Switchbox = { Vector3(-70.0f,-100.0f,0.0f),Vector3(70.0f,100.0f,100.0f) };
	mSwitchBoxCollider->SetObjectBox(Switchbox);
}

void SwitchCollider::UpdateGameObject(float _deltaTime)
{
	// �X�C�b�`�̃t���O��false�ɖ߂�
	Switch::mFollowSwitchFlag = false;
}

void SwitchCollider::OnCollision(const GameObject& _hitObject)
{
	//�q�b�g�����I�u�W�F�N�g�̃^�O���擾
	ObjTag hitObjectTag = _hitObject.GetTag();

	// �X�C�b�`�Ɠ������������A�X�C�b�`�t���O��false�̎�
	if (hitObjectTag == ObjTag::ePlayerLegs && !Switch::mFollowSwitchFlag)
	{
		// �t���O��true�ɂ���
		Switch::mFollowSwitchFlag = true;

		mLinkageColor = mSwitchColor;
	}
}
