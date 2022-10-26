#include "pch.h"

// �R���X�g���N�^
LegsCollider::LegsCollider(Player* _owner, const ObjTag& _objectTag, const SceneBase::SceneType _sceneTag)
	:GameObject(ObjTag::ePlayerLegs)
	, mIsGround(false)
	, mOwner(_owner)
{
	//�v���C���[�����̓����蔻��(�{�b�N�X)
	mLegsBoxCollider = new BoxCollider(this, GameObject::ObjTag::ePlayerLegs, GetOnCollisionFunc());
	AABB Legsbox = { Vector3(-20.0f,-20.0f,-10.0f),Vector3(20.0f,20.0f,5.0f) };
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
	ObjTag hitObjectTag = _hitObject.GetTag();
	
	if (hitObjectTag == ObjTag::eGround)
	{
		// �ڒn�t���O��true�ɂ���
		mIsGround = true;
	}

	if (hitObjectTag == ObjTag::eSwitchCenter && Player::mOperable)
	{
		mOwner->SetReturnPos(_hitObject.GetPosition());
	}
}
