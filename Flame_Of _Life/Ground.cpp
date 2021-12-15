/*
@brief	�C���N���[�h
*/
#include "pch.h"


Ground::Ground(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag, const groundTag& _tag)
	:GameObject(_sceneTag, _objectTag)
	, mAlphaNum(0)
	, mAlphaTiming(0)
	, MRedTime(100)
	, MGreenTime(300)
	, MBlueTime(500)
	, mCount(1)
	, MAlphaMax(1.2f)
	, MAlphaMin(-0.5f)
	, MAlphaValue(0.01f)
	, mAlphaChange(true)
	, mFirstFlag(true)
	, mStayPlayer(false)
	, mGroundTag(_tag)
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
	AABB box = { Vector3(13.0f,-20.0f,0.0f),Vector3(-13.0f,16.5f,9.0f) };
	mSelfBoxCollider->SetObjectBox(box);
}

void Ground::UpdateGameObject(float _deltaTime)
{
	mAabb = mSelfBoxCollider->GetWorldBox();

	if (MBlueTime >= mCount)
	{
		mCount++;
	}

	// ���ڂ̏���
	if (mFirstFlag)
	{
		// �^�O��RGBalpha��������
		if (mGroundTag == groundTag::RGBalpha)
		{
			// ���̐F�Ȃǂ�ݒ肷��
			mInit();
		}
		// �^�O��alpha��������
		else if (mGroundTag == groundTag::alpha)
		{
			// �F�����ɐݒ肷��
			mColor = Vector3(1.0f,0.0f,1.0f);
		}
	}

	// �����ɂȂ鏰�������炩�A�^�C�~���O�ƃJ�E���g����v������
	if ((mGroundTag != groundTag::notAlpha && mGroundTag != groundTag::stayAlpha) && mAlphaTiming <= mCount)
	{
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
		else if (mAlpha >= MAlphaMax && mGroundTag != groundTag::stayAlpha)
		{
			mAlphaChange = true;
		}
	}

	/*if (mGroundTag == stayAlpha && mStayPlayer)
	{
		mAlpha += MAlphaValue;
	}*/

	// ���l��0.0�ȉ��ɂȂ�����A���ARGB�̐F�����Ă��鏰��������
	if (mAlpha <= 0.0f &&( mGroundTag == groundTag::RGBalpha/* || mGroundTag == stayAlpha*/))
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
	// �v���C���[�Ɠ������Ă��邩�̃t���O��false�ɖ߂�
	mStayPlayer = false;
}

void Ground::OnCollision(const GameObject& _hitObject)
{
	//�q�b�g�����I�u�W�F�N�g�̃^�O���擾
	mTag = _hitObject.GetTag();

	// ���Ɛݒu�����Ƃ�
	if (mTag == ground)
	{
		// �ڒn�t���O��true�ɂ���
		mStayPlayer = true;
	}
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
		// ���l�̕ς��^�C�~���O���Z�b�g����
		mAlphaTiming = MRedTime;
		break;
	case green:
		mColor = Color::Green;
		// ���l�̕ς��^�C�~���O���Z�b�g����
		mAlphaTiming = MGreenTime;
		break;
	case blue:
		mColor = Color::Yellow;
		// ���l�̕ς��^�C�~���O���Z�b�g����
		mAlphaTiming = MBlueTime;
		break;
	}
}
