#include "pch.h"

// �R���X�g���N�^
LegsCollider::LegsCollider(Player* _owner, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	:GameObject(_sceneTag, _objectTag)
	, mIsGround(false)
	, mOwner(_owner)
{
	//�v���C���[�����̓����蔻��(�{�b�N�X)
	mLegsBoxCollider = new BoxCollider(this, ColliderTag::playerLegsTag, GetOnCollisionFunc());
	AABB Legsbox = { Vector3(-30.0f,-30.0f,-10.0f),Vector3(30.0f,30.0f,5.0f) };
	mLegsBoxCollider->SetObjectBox(Legsbox);
}

void LegsCollider::UpdateGameObject(float _deltaTime)
{
	SetPosition(mOwner->GetPosition());
	mAabb = mLegsBoxCollider->GetWorldBox();
	//mIsGround = false;
}

// �����蔻��
void LegsCollider::OnCollision(const GameObject& _hitObject)
{
	//�q�b�g�����I�u�W�F�N�g�̃^�O���擾
	Tag hitObjectTag = _hitObject.GetTag();
	
	if (hitObjectTag == Tag::ground ||
		hitObjectTag == Tag::Switch)
	{
		// �ڒn�t���O��true�ɂ���
		mIsGround = true;
	}

	if (hitObjectTag == Tag::SwitchCenter && Player::mOperable)
	{
		mOwner->SetReturnPos(_hitObject.GetPosition());
	}
}
