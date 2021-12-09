#include "pch.h"

// �R���X�g���N�^
FireObject::FireObject(Candle* _owner, const Vector3& _size, const Tag& _objectTag)
	: GameObject(GetScene(), _objectTag)
	, mOwner(_owner)
	, MAddPos(160.0f)
{
	//GameObject�����o�ϐ��̏�����
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(mOwner->GetPosition());

	//��������Player�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mMeshComponent = new MeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Player/Candle/Flame_plane.gpmesh"));

	//��]����                        ����]����l
	float radian = Math::ToRadians(180.0f);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::UnitZ, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}

/*
�X�V����
*/
void FireObject::UpdateGameObject(float _deltaTime)
{
	Vector3 tmp = mOwner->GetPosition();
	tmp.z += MAddPos;
	SetPosition(tmp);
}