#include "pch.h"

BackGround::BackGround(const Vector3 _pos, const BackGroundType _type)
	: GameObject()
{
	// MeshComponent�𐶐����邱�ƂŎ����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mMeshComponent = new MeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Books/Book_1.gpmesh"));

	//GameObject�����o�ϐ��̏�����
	SetScale(Vector3(10.0f, 10.0f, 10.0f));	// �X�P�[��
	SetPosition(_pos);						// �|�W�V����
	mAlpha = 0.3f;							// ���l

	// �^�C�v�ʂŐF��ύX
	if (_type == BackGroundType::eBGtypeOne)
	{
		mColor = Vector3(1.3f, 1.3f, 1.3f);
	}
	else
	{
		mColor = Vector3 (0.68f, 0.85f, 0.9f);
	}
}