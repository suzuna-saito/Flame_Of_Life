#include "pch.h"

ItemCat::ItemCat(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, _objectTag)
	, mCollisionFlag(false)
{
	//GameObject�����o�ϐ��̏�����
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	//Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mMeshComponent = new MeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Environment/Item/Cat.gpmesh"));

	//�A�C�e���̓����蔻��
	mSelfBoxCollider = new BoxCollider(this, ColliderTag::itemTag, GetOnCollisionFunc());
	AABB box = { Vector3(13.0f,-20.0f,0.0f),Vector3(-13.0f,16.5f,9.0f) };
	mSelfBoxCollider->SetObjectBox(box);

	//��]����                        ����]����l
	float radian = Math::ToRadians(180.0f);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::UnitZ, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);

}


void ItemCat::UpdateGameObject(float _deltaTime)
{
	// �t���O���オ���Ă�����
	if (mCollisionFlag && GetState() != Disabling)
	{
		// �X�e�[�g��disabl�ɂ���
		SetState(State::Disabling);

		Rose::mItemCount--;
	}
}


void ItemCat::OnCollision(const GameObject& _hitObject)
{
	//�q�b�g�����I�u�W�F�N�g�̃^�O���擾
	mTag = _hitObject.GetTag();

	// �v���C���[�Ƃ��̃I�u�W�F�N�g������������
	if (mTag == item)
	{
		// ���������̂Ńt���O���グ��
		mCollisionFlag = true;

		// �`�����߂�
		mMeshComponent->SetVisible(false);
	}
}
