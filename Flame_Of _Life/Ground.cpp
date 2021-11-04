/*
@brief	�C���N���[�h
*/
#include "pch.h"


Ground::Ground(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	:GameObject(_sceneTag, _objectTag)
	, mAlphaCount(0)
	, mAlphaAdd(0.01f)
	, mAlphaSub(-0.01f)
	, mAlphaChange(true)
{
	//GameObject�����o�ϐ��̏�����
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	mColor = Vector3(0.5f,0.3f,0.7f);

	//Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mMeshComponent = new MeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Environment/Books/Book_1.gpmesh"));
	//mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Environment/Carpets/Carpet.gpmesh"));

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

void Ground::UpdateGameObject(float _deltaTime)
{
	mAabb = mSelfBoxCollider->GetWorldBox();
	if (mAlphaChange)
	{
		mAlpha += mAlphaSub;
	}
	else
	{
		mAlpha += mAlphaAdd;
	}

	if (mAlpha <= 0.0f)
	{
		mAlphaChange = false;
	}
	else if (mAlpha >= 1.0f)
	{
		mAlphaChange = true;
	}

	/*if (mAlphaChange)
	{
		mAlphaSub *= -1.0f;
	}*/

}
