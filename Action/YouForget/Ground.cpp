/*
@brief	�C���N���[�h
*/
#include "pch.h"

// �ÓI�����o�ϐ��̏�����
int Ground::mTypeNum = 0;

Ground::Ground(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag, const groundTag& _tag)
	:GameObject(_sceneTag, _objectTag)
	, mAlphaNum(0)
	, MAlphaAddSpeed(4.5f)
	, MAlphaSubSpeed(0.7f)
	, MAlphaMax(1.2f)
	, mGroundTag(_tag)
	, mAlphaColorTag(alphaColor::red)
{
	//GameObject�����o�ϐ��̏�����
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	//Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mMeshComponent = new MeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Books/Book_1.gpmesh"));

	//�n�ʂ̓����蔻��
	mSelfBoxCollider = new BoxCollider(this, ColliderTag::groundTag, GetOnCollisionFunc());
	AABB box = { Vector3(-14.5f,-21.5f,0.0f),Vector3(14.5f,20.0f,9.0f) };
	mSelfBoxCollider->SetObjectBox(box);

	// ���̐F�Ȃǂ�ݒ肷��
	if (mGroundTag == groundTag::RGBalpha)
	{
		mInit();
	}

	// �����x
	if (mGroundTag == groundTag::RGBalpha)
	{
		mAlpha = 0.0f;
	}
}

void Ground::UpdateGameObject(float _deltaTime)
{
	mAabb = mSelfBoxCollider->GetWorldBox();

	// �X�C�b�`�������Ă����炩�A������ł�X�C�b�`�̐F�Ə��̐F���ꏏ��������
	if (Switch::mSwitchFlag && mGroundTag == groundTag::RGBalpha &&
		mAlphaColorTag == SwitchCollider::mLinkageColor)
	{
		// �����������x��������
		if (mAlpha <= MAlphaMax)
		{
			mAlpha += MAlphaAddSpeed* _deltaTime;
		}
	}
	else if(mGroundTag != groundTag::notAlpha)
	{
		// �����������x��������
		if (mAlpha >= 0.0f)
		{
			mAlpha -= MAlphaSubSpeed * _deltaTime;
		}
	}

	if (!Player::mOperable && mAlpha <= 1.0f)
	{
		mAlpha += MAlphaAddSpeed * _deltaTime;
	}
}

void Ground::OnCollision(const GameObject& _hitObject)
{
}

// ���̐F�A���l�̕ς��^�C�~���O��ݒ肷��
void Ground::mInit()
{

	// �����_����mAlphaNam��ݒ�
	mAlphaNum = rand() % mTypeNum;

	switch (mAlphaNum)
	{
	case (int)alphaColor::red:
		mColor = Color::Red;
		// ���F�̏��Ȃ̂���ݒ�
		mAlphaColorTag = alphaColor::red;
		break;
	case (int)alphaColor::green:
		mColor = Color::Green;
		// ���F�̏��Ȃ̂���ݒ�
		mAlphaColorTag = alphaColor::green;
		break;
	case (int)alphaColor::yellow:
		mColor = Color::Yellow;
		break;
	}
}
