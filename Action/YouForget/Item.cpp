#include "pch.h"

Item::Item(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag, const int _num)
	: ItemBase(_sceneTag, _objectTag)
	, ItemNumber(_num)
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
	//mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Item/Sphere.gpmesh"));
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Item/Puzzle.gpmesh"));

	// �G�t�F�N�g
	// �A�C�e���̌��ɂ���G�t�F�N�g
	mItemEffectManager = new ItemEffectManager(_objectTag, _sceneTag, this);

	//�����蔻��
	mSelfBoxCollider = new BoxCollider(this, ColliderTag::itemTag, GetOnCollisionFunc());
	AABB box = { Vector3(3.0f,-3.0f,-3.0f),Vector3(-3.0f,4.0f,3.0f) };
	mSelfBoxCollider->SetObjectBox(box);

	//��]����                        ����]����l
	float radianZ = Math::ToRadians(90.0f);
	Quaternion rot = this->GetRotation();
	Quaternion incZ(Vector3::UnitZ, radianZ);
	Quaternion target = Quaternion::Concatenate(rot, incZ);
	SetRotation(target);

	float radianY = Math::ToRadians(-80.0f*_num);
	rot = this->GetRotation();
	Quaternion incY(Vector3::UnitY, radianY);
	target = Quaternion::Concatenate(rot, incY);
	SetRotation(target);

	float radianX = Math::ToRadians(-40.0f);
	rot = this->GetRotation();
	Quaternion incX(Vector3::UnitX, radianX);
	target = Quaternion::Concatenate(rot, incX);
	SetRotation(target);

	// �A�C�e���̎�ނ�����
	mItemType();
	
	mColor = Vector3 (1.0f, 1.0f, 2.0f);
}


void Item::UpdateGameObject(float _deltaTime)
{
	// �v���C���[�Ɠ������Ă��Ȃ�������
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
	// �v���C���[�Ɠ������Ă���
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


void Item::OnCollision(const GameObject& _hitObject)
{
	// �v���C���[������\��Ԃ̎��ɓ���������
	if (Player::mOperable)
	{
		// ���������̂Ńt���O���グ��
		mCollisionFlag = true;

		// �`�����߂�
		mMeshComponent->SetVisible(false);
	}
}

void Item::mItemType()
{
	// ���������Ԗڂ��ɂ���Ď�ނ�ς���
	switch (ItemNumber)
	{
	case(0):
		mItemName = itemNames::cat;
		break;
	case(1):
		mItemName = itemNames::chair;
		break;
	case(2):
		mItemName = itemNames::chara;
		break;
	default:
		break;
	}

}
