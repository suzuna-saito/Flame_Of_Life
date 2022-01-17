/*
@brief	�C���N���[�h
*/
#include "pch.h"

// �ÓI�����o�ϐ�
float Switch::mDistance = 0.0f;
bool Switch::mSwitchFlag = false;
Ground::alphaColor Switch::mSwitchColor = Ground::alphaColor::red;


Switch::Switch(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag,const Ground::alphaColor& _tag)
	:GameObject(_sceneTag, _objectTag)
{
	//GameObject�����o�ϐ��̏�����
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	mSwitchColor = _tag;

	//Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mMeshComponent = new MeshComponent(this);

	// �^�O�ɂ����gpmesh��ύX
	switch (_tag)
	{
	case Ground::alphaColor::red:
		//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
		mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Switch/RedSwitch.gpmesh"));
		break;
	case Ground::alphaColor::green:
		//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
		mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Switch/GreenSwitch.gpmesh"));
		break;
	case Ground::alphaColor::yellow:
		break;
	default:
		break;
	}

	//�����蔻��
	mSelfBoxCollider = new BoxCollider(this, ColliderTag::groundTag, GetOnCollisionFunc());
	AABB box = { Vector3(13.0f,-20.0f,0.0f),Vector3(-13.0f,16.5f,9.0f) };
	mSelfBoxCollider->SetObjectBox(box);
}

void Switch::UpdateGameObject(float _deltaTime)
{
	mAabb = mSelfBoxCollider->GetWorldBox();

	//// �v���C���[�ƁA�X�C�b�`�̋������v�Z
	//if (Player::mGetPos().x >= mPosition.x)  // �v���C���[�̒l�̕����傫�����
	//{
	//	mDistance = Player::mGetPos().x - mPosition.x;
	//}
	//else
	//{
	//	mDistance = mPosition.x - Player::mGetPos().x ;
	//}


	//// mDistance ���}�C�i�X��������
	//if (mDistance < 0.0f)
	//{
	//	// ���̐��ɂ���
	//	mDistance *= -1;
	//}


}

void Switch::mSubtraction(Vector3 _pPos, Vector3 _sPos)
{
	//(_pPos.x - _sPos.x)* (_pPos.x - _sPos.x);

	
}

void Switch::OnCollision(const GameObject& _hitObject)
{
}
