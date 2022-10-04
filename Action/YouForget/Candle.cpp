#include "pch.h"

// �ÓI�����o�ϐ�
bool Candle::mGoalFlag = false; // �S�[���������ǂ���

Candle::Candle(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::SceneType _sceneTag)
	: GameObject(_sceneTag, _objectTag)
	, mDrawFireFlag(false)
{
	// �S�[���������ǂ����t���O��false�ɂ���
	mGoalFlag = false;

	//GameObject�����o�ϐ��̏�����
	mTag = _objectTag;   // �I�u�W�F�N�g�^�O
	SetScale(_size);     // �I�u�W�F�N�g�T�C�Y
	SetPosition(_pos);   // �I�u�W�F�N�g�̃|�W�V����

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
	// �S�[�����āA�΂�`�悵�Ă��Ȃ�������
	if (mGoalFlag && !mDrawFireFlag)
	{
		// �낤�����̉΂𐶐�
		new FireObject(this, mTag, GetScene());
		// �`�悵�Ă���̂Ńt���O��false�ɂ���
		mDrawFireFlag = true;
	}
}

/*
@fn		�낤�������q�b�g�������̏���
@param	_hitObject �q�b�g�����Ώۂ̃Q�[���I�u�W�F�N�g�̃A�h���X
*/
void Candle::OnCollision(const GameObject& _hitObject)
{
	// �S�[���������ǂ����t���O��true�ɂ���
	mGoalFlag = true;
}
