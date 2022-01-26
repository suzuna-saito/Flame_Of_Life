#include "pch.h"

// �ÓI�����o�@
Ground::alphaColor SwitchCollider::mLinkageColor = Ground::alphaColor::red;

// �R���X�g���N�^
SwitchCollider::SwitchCollider(Switch* _owner,const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	:GameObject(_sceneTag, _objectTag)
	, mOwner(_owner)
{
	SetPosition(_owner->GetPosition());

	mTag = Tag::SwitchCenter;

	//�X�C�b�`���S�̓����蔻��(�{�b�N�X)
	mSwitchBoxCollider = new BoxCollider(this, ColliderTag::switchTag, GetOnCollisionFunc());
	AABB Switchbox = { Vector3(-50.0f,-80.0f,0.0f),Vector3(50.0f,80.0f,100.0f) };
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
	Tag hitObjectTag = _hitObject.GetTag();

	// �X�C�b�`�Ɠ������������A�X�C�b�`�t���O��false�̎�
	if (hitObjectTag == Tag::player && !Switch::mSwitchFlag)
	{
		// �t���O��true�ɂ���
		Switch::mSwitchFlag = true;
	}

	// �X�C�b�`�̐F��
	switch (mOwner->GetSwitchColor())
	{
	case(Switch::switchColor::red):  // �Ԃ�������
		// ���ƘA�g������F��Ԃɐݒ�
		mLinkageColor = Ground::alphaColor::red;
		break;
	case(Switch::switchColor::green):  // �΂�������
		// ���ƘA�g������F��΂ɐݒ�
		mLinkageColor = Ground::alphaColor::green;
		break;
	case(Switch::switchColor::yellow):  // ���F��������
		// ���ƘA�g������F�����F�ɐݒ�
		mLinkageColor = Ground::alphaColor::yellow;
		break;
	default:
		break;
	}

	/*if (mOwner->GetSwitchColor() == Switch::switchColor::green)
	{
		printf("��\n");
	}
	else
	{
		printf("��\n");
	}*/
}
