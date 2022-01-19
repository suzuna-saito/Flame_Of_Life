/*
@brief	�C���N���[�h
*/
#include "pch.h"

// �ÓI�����o�ϐ��̏�����
int Ground::mTypeNum = 0;

Ground::Ground(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag, const groundTag& _tag)
	:GameObject(_sceneTag, _objectTag)
	, mAlphaNum(0)
	, mAlphaTiming(0)
	/*, MRedTime(100)
	, MGreenTime(300)
	, MYellowTime(500)*/
	, mCount(1)
	, MAlphaAddSpeed(0.05f)
	, MAlphaSubSpeed(0.01f)
	, MAlphaMax(1.2f)
	, MAlphaMin(-0.5f)
	, MAlphaValue(0.01f)
	, mAlphaChange(true)
	, mFirstFlag(true)
	, mStayPlayer(false)
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
	AABB box = { Vector3(13.0f,-20.0f,0.0f),Vector3(-13.0f,16.5f,9.0f) };
	mSelfBoxCollider->SetObjectBox(box);

	/* �����̎�������� */
	srand(time(NULL));

	// �����x
	if (mGroundTag == groundTag::RGBalpha)
	{
		mAlpha = 0.0f;
	}
}

void Ground::UpdateGameObject(float _deltaTime)
{
	mAabb = mSelfBoxCollider->GetWorldBox();

	/*if (MYellowTime >= mCount)
	{
		mCount++;
	}*/

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

		//�@�t�@�[�X�g�t���O��false�ɂ���
		mFirstFlag = false;
	}

	//// �X�C�b�`�̐F�Ə��̐F���ꏏ��������
	//if (Switch::mSwitchFlag && mAlphaColorTag == Switch::mSwitchColor)
	//{
	//	// �����������x��������
	//	if (mAlpha <= 1.0f)
	//	{
	//		mAlpha += MAlphaAddSpeed;
	//	}
	//}

	// �X�C�b�`�̐F�Ə��̐F���ꏏ��������
	if (mGroundTag == groundTag::RGBalpha)
	{
		// �X�C�b�`�������Ă�����
		if (Switch::mSwitchFlag)
		{
			// �����������x��������
			if (mAlpha <= 1.0f)
			{
				mAlpha += MAlphaAddSpeed;
			}
		}
		else
		{
			// �����������x��������
			if (mAlpha >= 0.0f)
			{
				mAlpha -= MAlphaSubSpeed;
			}
		}
		/*mAlpha -= Switch::mGetDistance()*0.005;

		if (mAlpha <= 0.0f)
		{
			mAlpha = 0.0f;
		}*/
	}

	
	//// �����ɂȂ鏰�������炩�A�^�C�~���O�ƃJ�E���g����v������
	//if (mGroundTag != groundTag::notAlpha && mAlphaTiming <= mCount)
	//{
	//	// mAlphaChange�t���O�����ă��l���グ�邩�����邩�ς���
	//	if (mAlphaChange)
	//	{
	//		mAlpha -= MAlphaValue;
	//	}
	//	else
	//	{
	//		mAlpha += MAlphaValue;
	//	}

	//	// ��萔�܂ł�������t���O��ύX����
	//	if (mAlpha <= MAlphaMin)
	//	{
	//		mAlphaChange = false;
	//	}
	//	else if (mAlpha >= MAlphaMax)
	//	{
	//		mAlphaChange = true;
	//	}
	//}
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
