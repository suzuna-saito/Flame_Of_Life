/*
@brief	�C���N���[�h
*/
#include "pch.h"

// �ÓI�����o�ϐ�
// �X�C�b�`�������Ă��邩�ǂ���
bool Switch::mSwitchFlag = false;

Switch::Switch(const Vector3& _pos, const Vector3& _size, const CollisionTag& _objectTag, const SceneBase::SceneType _sceneTag, const switchColor& _color)
	:GameObject(_sceneTag, _objectTag)
{
	//GameObject�����o�ϐ��̏�����
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	// �X�C�b�`�̐F��ݒ�
	mSwitchColor = _color;

	//Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mMeshComponent = new MeshComponent(this);

	// �^�O�ɂ����gpmesh��ύX
	switch (_color)
	{
	case switchColor::red:
		//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
		mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Switch/RedSwitch.gpmesh"));
		/*mRedSwitchFlag = true;*/
		break;
	case switchColor::green:
		//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
		mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Switch/GreenSwitch.gpmesh"));
		/*mGreenSwitchFlag = true;*/
		break;
	case switchColor::yellow:
		break;
	default:
		break;
	}

	//�����蔻��
	mSelfBoxCollider = new BoxCollider(this, ColliderTag::groundTag, GetOnCollisionFunc());
	AABB box = { Vector3(14.5f,-21.5f,0.0f),Vector3(-14.5f,20.0f,9.0f) };
	mSelfBoxCollider->SetObjectBox(box);

	// �X�C�b�`���S�����蔻��̐���
	mSwitchCenter = new SwitchCollider(this, CollisionTag::SwitchCenter, _sceneTag);

}

void Switch::UpdateGameObject(float _deltaTime)
{
	mAabb = mSelfBoxCollider->GetWorldBox();

}

void Switch::OnCollision(const GameObject& _hitObject)
{
}
