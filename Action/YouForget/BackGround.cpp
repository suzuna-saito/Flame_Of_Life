#include "pch.h"

BackGround::BackGround(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag,const int _type)
	:GameObject(_sceneTag, _objectTag)
	, mType(_type)
{
	//GameObject�����o�ϐ��̏�����
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	// Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mMeshComponent = new MeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Books/Book_1.gpmesh"));

	if (mType == 35)
	{
		// �F��ݒ�
		mColor = Vector3(1.3f, 1.3f, 1.3f);
		// �����x��ݒ�
		mAlpha = 0.3f;
	}
	else
	{
		// �F��ݒ�
		mColor = Vector3 (0.68f, 0.85f, 0.9f);
		// �����x��ݒ�
		mAlpha = 0.3f;
	}
	

}
