#include "pch.h"

ItemTest::ItemTest(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag, const int _num)
	: ItemBase(_sceneTag, _objectTag)
{
	//GameObject�����o�ϐ��̏�����
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	// �|�W�V�����������ő�̍���
	mMaxMove += mPosition.z;
	// �|�W�V�����������ŏ��i�����|�W�j
	mMinMove = mPosition.z;

	//Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mMeshComponent = new MeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Item/Sphere.gpmesh"));

	//�����蔻��
	mSelfBoxCollider = new BoxCollider(this, ColliderTag::itemTag, GetOnCollisionFunc());
	AABB box = { Vector3(100.0f,-100.0f,-100.0f),Vector3(-100.0f,100.0f,100.0f) };
	mSelfBoxCollider->SetObjectBox(box);

	// ���������Ԗڂ��ɂ���Ď�ނ�ς���
	switch (_num)
	{
	case(1):
		mItemName = itemNames::cat;
		break;
	case(2):
		mItemName = itemNames::chair;
		break;
	case(3):
		mItemName = itemNames::chara;
		break;
	default:
		break;
	}

	mColor = Vector3(0.5f, 0.5f, 1.5f);
}


void ItemTest::UpdateGameObject(float _deltaTime)
{
	// �t���O���������Ă�����
	if (!mCollisionFlag)
	{
		// �t���O�����ăA�C�e���̓������㉺������
		if (mUpFlag)
		{
			mPosition.z += mMove * _deltaTime;
		}
		else
		{
			mPosition.z -= mMove * _deltaTime;
		}
		// ��萔�܂ł�������t���O��ύX����
		if (mPosition.z >= mMaxMove)
		{
			mUpFlag = false;
			
		}
		else if(mPosition.z <= mMinMove)
		{
			mUpFlag = true;
			
		}

		SetPosition(mPosition);
	}
	// �t���O���オ���Ă�����
	else if (mCollisionFlag && GetState() != State::Disabling)
	{
		// �X�e�[�g��disabl�ɂ���
		SetState(State::Disabling);

		// �A�C�e���J�E���g�����炷
		ItemBase::mItemCount--;

		// �擾�����A�C�e�����f�[�^�\���Ɋi�[����
		mGetNames.push_back(mItemName);
	}
}


void ItemTest::OnCollision(const GameObject& _hitObject)
{
	// ���������̂Ńt���O���グ��
	mCollisionFlag = true;

	// �`�����߂�
	mMeshComponent->SetVisible(false);
}
