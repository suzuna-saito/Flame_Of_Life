/*
@brief	�C���N���[�h
*/
#include "pch.h"

// �ÓI�����o�ϐ�

int Candle::mCandleCount = 0; // �΂����Ă�낤�����̖{��

Candle::Candle(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, _objectTag)
	, mFireScele(Vector3(10.0f,10.0f,10.0f))
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
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Candle/Candle_2.gpmesh"));

	//�낤�����̓����蔻��
	mSelfBoxCollider = new BoxCollider(this, ColliderTag::candleTag, GetOnCollisionFunc());
	AABB box = { Vector3(-3.0f,-1.0f,0.0f),Vector3(3.0f,1.0f,10.0f) };
	mSelfBoxCollider->SetObjectBox(box);
}

/*
@fn		�낤�����̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void Candle::UpdateGameObject(float _deltaTime)
{
	if (mFireFlag && !mDrawFireFlag)
	{
		// �낤�����̉΂𐶐�
		new FireObject(this, mFireScele, mTag, GetScene());

		mDrawFireFlag = true;

		mCandleCount++;
	}
}

/*
@fn		�낤�������q�b�g�������̏���
@param	_hitObject �q�b�g�����Ώۂ̃Q�[���I�u�W�F�N�g�̃A�h���X
*/
void Candle::OnCollision(const GameObject& _hitObject)
{
	mFireFlag = true;
}
