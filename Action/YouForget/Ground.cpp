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
	, MAlphaSubSpeed(0.8f)
	, MAlphaMax(1.2f)
	, mGroundTag(_tag)
	, mAlphaColorTag(alphaColor::red)
	, mIsPlayer(false)
	, mBeforeIsPlayer(false)
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
	else
	{
		mColor = Vector3(1.0f,1.0f,1.0f);
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

	// ���̓����x��0��菬����������܂��́A�X�C�b�`�������ꂽ��
	if (mAlpha <= 0.0f || Switch::mSwitchFlag)
	{
		// �v���C���[������Ă��Ȃ���������ɂ���
		mBeforeIsPlayer = false;
	}

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
	// �v���C���[������Ă��鏰��������
	else if (mIsPlayer)
	{
		// �����������x��������
		if (mAlpha <= MAlphaMax-0.7f)
		{
			mAlpha += (MAlphaAddSpeed * 1.5f)*_deltaTime;
		}
	}

	// �X�C�b�`�������Ă��Ȃ����A�v���C���[������Ă��Ȃ�������
	if(!Switch::mSwitchFlag && mGroundTag != groundTag::notAlpha && !mIsPlayer && !mBeforeIsPlayer ||
		Switch::mSwitchFlag && mGroundTag != groundTag::notAlpha && mAlphaColorTag != SwitchCollider::mLinkageColor)
	{
		// �����������x��������
		if (mAlpha >= 0.0f)
		{
			mAlpha -= MAlphaSubSpeed * _deltaTime;
		}
	}
	else if (mGroundTag != groundTag::notAlpha && !mIsPlayer && mBeforeIsPlayer)
	{
		// �����������x��������
		if (mAlpha >= 0.0f)
		{
			mAlpha -= (MAlphaSubSpeed*1.9f) * _deltaTime;
		}
	}

	// �v���C���[����������
	if (!Player::mOperable && mAlpha <= 1.0f)
	{
		// ����������悤�ɂ���
		mAlpha += MAlphaAddSpeed * _deltaTime;
	}


	// �v���C���[���O����Ă��Ȃ��Ă��A������Ă�����
	if (mBeforeIsPlayer != mIsPlayer && !mBeforeIsPlayer)
	{
		mBeforeIsPlayer = mIsPlayer;
	}
	

	mIsPlayer = false;
}

void Ground::OnCollision(const GameObject& _hitObject)
{
	//�q�b�g�����I�u�W�F�N�g�̃^�O���擾
	Tag hitObjectTag = _hitObject.GetTag();

	if (hitObjectTag == Tag::playerLegs)
	{
		mIsPlayer = true;
	}
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
