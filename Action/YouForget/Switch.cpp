#include "pch.h"

// �ÓI�����o�ϐ��̏�����
bool Switch::mFollowSwitchFlag = false;	// �X�C�b�`�������Ă��邩�ǂ��� true:�����Ă���

Switch::Switch(const Vector3 _pos,const Ground::GroundColor _color)
	:GameObject(ObjTag::eGround)
{
	// MeshComponent�𐶐����邱�ƂŎ����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mMeshComponent = new MeshComponent(this);

	//�����蔻��
	mSelfBoxCollider = new BoxCollider(this, mTag, GetOnCollisionFunc());
	AABB box = { Vector3(14.5f,-21.5f,0.0f),Vector3(-14.5f,20.0f,9.0f) };
	mSelfBoxCollider->SetObjectBox(box);

	// GameObject�����o�ϐ��̏�����
	SetScale(Vector3(10.0f, 10.0f, 10.0f));	// �X�P�[��
	SetPosition(_pos);						// �|�W�V����

	//// �^�O�ɂ����gpmesh��ύX
	//switch (_color)
	//{
	//case switchColor::red:
	//	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Switch/RedSwitch.gpmesh"));
	//	break;
	//case switchColor::green:
	//	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Switch/GreenSwitch.gpmesh"));
	//	break;
	//default:
	//	break;
	//}

	// �X�C�b�`���S�����蔻��̐���
	mSwitchCenter = new SwitchCollider(this, ObjTag::eSwitchCenter, SceneBase::mIsSceneType, _color);
}

void Switch::UpdateGameObject(float _deltaTime)
{
	mAabb = mSelfBoxCollider->GetWorldBox();

}