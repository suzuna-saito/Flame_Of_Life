/*
@brief	�C���N���[�h
*/
#include "pch.h"


Ground::Ground(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag, const bool _alphaFlag)
	:GameObject(_sceneTag, _objectTag)
	, mAlphaNum(0)
	, mAlphaTiming(0)
	, MTwoTime(250)
	, MThreeTime(500)
	, mCount(1)
	, MAlphaMax(1.2f)
	, MAlphaMin(-0.5f)
	, MAlphaValue(0.01f)
	, mAlphaChange(true)
	, mAlphaGround(_alphaFlag)
	, mFirstFlag(true)
{
	/* �����̎�������� */
	srand(time(NULL));

	//GameObject�����o�ϐ��̏�����
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	//SetState(State::Disabling);
	//Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mMeshComponent = new MeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Environment/Books/Book_1.gpmesh"));

	//�n�ʂ̓����蔻��
	mSelfBoxCollider = new BoxCollider(this, ColliderTag::groundTag, GetOnCollisionFunc());
	AABB box = { Vector3(13.0f,-20.0f,0.0f),Vector3(-13.0f,16.5f,9.0f) };
	mSelfBoxCollider->SetObjectBox(box);
}

void Ground::UpdateGameObject(float _deltaTime)
{
	mAabb = mSelfBoxCollider->GetWorldBox();

	if (MThreeTime >= mCount)
	{
		mCount++;
	}

	// �����ɂȂ鏰�������炩�A�^�C�~���O�ƃJ�E���g����v������
	if (mAlphaGround && mAlphaTiming <= mCount)
	{
		// ���ڂ̏�����������
		if (mFirstFlag)
		{
			// ���̐F�Ȃǂ�ݒ肷��
			mInit();
		}

		// mAlphaChange�t���O�����ă��l���グ�邩�����邩�ς���
		if (mAlphaChange)
		{
			mAlpha -= MAlphaValue;
		}
		else
		{
			mAlpha += MAlphaValue;
		}

		// ��萔�܂ł�������t���O��ύX����
		if (mAlpha <= MAlphaMin)
		{
			mAlphaChange = false;
		}
		else if (mAlpha >= MAlphaMax)
		{
			mAlphaChange = true;
		}
	}

	// ���l��0.0�ȉ��ɂȂ�����
	if (mAlpha <= 0.0f)
	{
		// �X�e�[�g��disabl�ɂ���
		SetState(State::Disabling);
	}
	else
	{
		SetState(State::Active);
	}

	//�@�t�@�[�X�g�t���O��false�ɂ���
	mFirstFlag = false;
}

// ���̐F�A���l�̕ς��^�C�~���O��ݒ肷��
void Ground::mInit()
{
	// �����_����mAlphaNam��ݒ�0~2
	mAlphaNum = rand() % 3;

	switch (mAlphaNum)
	{
	case red:
		mColor = Color::Red;
		break;
	case green:
		mColor = Color::Green;
		// ���l�̕ς��^�C�~���O���Z�b�g����
		mAlphaTiming = MTwoTime;
		break;
	case blue:
		mColor = Color::Blue;
		// ���l�̕ς��^�C�~���O���Z�b�g����
		mAlphaTiming = MThreeTime;
		break;
	}
}
