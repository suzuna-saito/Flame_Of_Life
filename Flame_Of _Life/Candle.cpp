/*
@brief	�C���N���[�h
*/
#include "pch.h"

Candle::Candle(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, _objectTag)
	, mFireFlag(false)
	, mDrawFireFlag(false)
{
	//GameObject�����o�ϐ��̏�����
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	//Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mMeshComponent = new MeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Player/Candle/Candle_2.gpmesh"));

	//�낤�����̓����蔻��
	mSelfBoxCollider = new BoxCollider(this, ColliderTag::groundTag, GetOnCollisionFunc());
	AABB box = { Vector3(-1.0f,-1.0f,0.0f),Vector3(1.0f,1.0f,0.7f) };
	mSelfBoxCollider->SetObjectBox(box);

	// �낤�����̉΂𐶐�
	new FireObject(this, Vector3(3.0f, 3.0f, 3.0f), mTag);
}

//void Candle::UpdateGameObject(float _deltaTime)
//{
//	if (mFireFlag && !mDrawFireFlag)
//	{
//		
//
//		mDrawFireFlag = true;
//	}
//}
