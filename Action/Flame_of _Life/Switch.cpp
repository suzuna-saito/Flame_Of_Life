/*
@brief	�C���N���[�h
*/
#include "pch.h"
#include <iostream>

// �ÓI�����o�ϐ�
float Switch::mDistance = 0.0f;
bool Switch::mSwitchFlag = false;
Switch::switchColor Switch::mSwitchColor = Switch::switchColor::red;

Switch::Switch(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag, const switchColor& _color)
	:GameObject(_sceneTag, _objectTag)
	/*, mRedSwitchFlag(false)
	, mGreenSwitchFlag(false)
	, mYellowSwitchFlag(false)*/
{
	//GameObject�����o�ϐ��̏�����
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	// �X�C�b�`�̐F��ݒ�
	mSwitchColor = _color;
	//mSwitchColor = _tag;

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
	AABB box = { Vector3(14.0f,-20.0f,0.0f),Vector3(-14.0f,16.5f,9.0f) };
	mSelfBoxCollider->SetObjectBox(box);

	// �X�C�b�`���S�����蔻��̐���
	mSwitchCenter = new SwitchCollider(this, _objectTag, _sceneTag);
}

void Switch::UpdateGameObject(float _deltaTime)
{
	mAabb = mSelfBoxCollider->GetWorldBox();

	// �X�C�b�`�������Ă����Ԃ�������
	/*if (mSwitchFlag)
	{
		switch (mSwitchColor)
		{
		case(Ground::alphaColor::red):

		default:
			break;
		}
	}*/

}

void Switch::OnCollision(const GameObject& _hitObject)
{
}
