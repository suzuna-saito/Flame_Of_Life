#include "pch.h"

// �ÓI�����o�ϐ��̏�����
int Ground::mTypeNum = 0;

Ground::Ground(const Vector3 _pos, const GroundType _tag)
	: GameObject(ObjTag::eGround)
	, MAlphaAddSpeed(4.5f)
	, MAlphaSubSpeed(0.8f)
	, MAlphaMax(1.2f)
	, MGroundType(_tag)
	, mAlphaColorTag(GroundColor::eRed)
	, mIsPlayer(false)
	, mBeforeIsPlayer(false)
{
	// MeshComponent�𐶐����邱�ƂŎ����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mMeshComponent = new MeshComponent(this);
	// Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Books/Book_1.gpmesh"));

	// �����蔻��
	mSelfBoxCollider = new BoxCollider(this, mTag, GetOnCollisionFunc());
	AABB box = { Vector3(-14.5f,-21.5f,0.0f),Vector3(14.5f,20.0f,9.0f) };
	mSelfBoxCollider->SetObjectBox(box);

	// GameObject�����o�ϐ��̏�����
	SetScale(Vector3(10.0f, 10.0f, 10.0f));		// �X�P�[��
	SetPosition(_pos);							// �|�W�V����

	// ���̐F�A�����x��ݒ�
	SetGroundInfo();
}

void Ground::SetGroundInfo()
{
	// �����ɂȂ�Ȃ�����������
	if (MGroundType == GroundType::eNotAlpha)
	{
		mColor = Color::White;				// �F�𔒂ɐݒ�
		return;
	}

	// �����_���Ő������擾
	int randNum = rand() % mTypeNum;

	// �l���Ԃƈ�v������
	if (randNum == (int)GroundColor::eRed)
	{
		mColor = Vector3(1.0f, 0.6f, 0.6f); // �F���������Ԃɐݒ�
		mAlphaColorTag = GroundColor::eRed;	// ���̐F�̎�ނ�Ԃɐݒ�
	}
	else
	{
		mColor = Color::LightGreen;			// �F�����΂ɐݒ�
		mAlphaColorTag = GroundColor::eGreen;
	}

	// �����x��0.0f�ɐݒ�
	mAlpha = 0.0f;
}

void Ground::UpdateGameObject(float _deltaTime)
{
	// AABB�𖈃��[�v�X�V
	mAabb = mSelfBoxCollider->GetWorldBox();

	// ���̓����x��0��菬����������܂��́A�X�C�b�`�������ꂽ��
	if (mAlpha <= 0.0f || Switch::mFollowSwitchFlag)
	{
		// �v���C���[������Ă��Ȃ���������ɂ���
		mBeforeIsPlayer = false;
	}

	// �X�C�b�`�������Ă����炩�A������ł�X�C�b�`�̐F�Ə��̐F���ꏏ��������
	if (Switch::mFollowSwitchFlag && MGroundType == GroundType::eAlpha &&
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
	if(!Switch::mFollowSwitchFlag && MGroundType != GroundType::eNotAlpha && !mIsPlayer && !mBeforeIsPlayer ||
		Switch::mFollowSwitchFlag && MGroundType != GroundType::eNotAlpha && mAlphaColorTag != SwitchCollider::mLinkageColor)
	{
		// �����������x��������
		if (mAlpha >= 0.0f)
		{
			mAlpha -= MAlphaSubSpeed * _deltaTime;
		}
	}
	else if (MGroundType != GroundType::eNotAlpha && !mIsPlayer && mBeforeIsPlayer)
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
	ObjTag hitObjectTag = _hitObject.GetTag();

	if (hitObjectTag == ObjTag::ePlayerLegs)
	{
		mIsPlayer = true;
	}
}
