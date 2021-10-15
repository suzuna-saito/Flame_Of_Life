/*
@brief	�C���N���[�h
*/
#include "pch.h"


Ground::Ground(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	:GameObject(_sceneTag, _objectTag)
{
	//GameObject�����o�ϐ��̏�����
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	//Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mMeshComponent = new MeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	//mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Environment/Carpets/Carpet_long_1.gpmesh"));
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Environment/Books/Book_1.gpmesh"));

	//�n�ʂ̓����蔻��
	mSelfBoxCollider = new BoxCollider(this, ColliderTag::groundTag, GetOnCollisionFunc());
	AABB box = { Vector3(13.0f,-20.0f,0.0f),Vector3(-13.0f,16.5f,9.0f) };
	mSelfBoxCollider->SetObjectBox(box);

	////��]����                        ����]����l
	//float radian = Math::ToRadians(180.0f);
	//Quaternion rot = this->GetRotation();
	//Quaternion inc(Vector3::UnitZ, radian);
	//Quaternion target = Quaternion::Concatenate(rot, inc);
	//SetRotation(target);
}