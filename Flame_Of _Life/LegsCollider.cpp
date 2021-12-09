#include "pch.h"

// �R���X�g���N�^
LegsCollider::LegsCollider(Player* _owner, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	:GameObject(_sceneTag, _objectTag)
	, mIsGround(false)
	, mOwner(_owner)
{
	//�v���C���[�����̓����蔻��(�{�b�N�X)
	mLegsBoxCollider = new BoxCollider(_owner, ColliderTag::playerLegsTag, GetOnCollisionFunc());
	AABB Legsbox = { Vector3(750.0f,-750.0f,0.0f),Vector3(-750.0f,750.0f,300.0f) };
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
	// �ڒn�t���O��true�ɂ���
	mIsGround = true;
	////�q�b�g�����I�u�W�F�N�g�̃^�O���擾
	//mTag = _hitObject.GetTag();

	//// ���Ɛݒu�����Ƃ�
	//if (mTag == ground)
	//{
	//}
}
