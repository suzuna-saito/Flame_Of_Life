#include "pch.h"

Item::Item(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag, const int _num)
	: ItemBase(_sceneTag, _objectTag)
	, mItemExistsTime(0)
	, MItemExistsOneTime(2100)
	, MItemExistsTwoTime(1700)
	, MItemExistsThreeTime(800)
	, mItemFlashingTime(200)
	, mItemExistsFlag(true)
	, mAlphaDownFlag(true)
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

	float radianY = Math::ToRadians(-80.0f*(int)_num);
	rot = this->GetRotation();
	Quaternion incY(Vector3::UnitY, radianY);
	target = Quaternion::Concatenate(rot, incY);
	SetRotation(target);

	float radianX = Math::ToRadians(-40.0f);
	rot = this->GetRotation();
	Quaternion incX(Vector3::UnitX, radianX);
	target = Quaternion::Concatenate(rot, incX);
	SetRotation(target);

	// �A�C�e���̃i���o�[�A�A�C�e���̑��ݎ���
	mItemType(_num);

	// �F
	mColor = Vector3(0.68f, 0.85f, 1.2f);

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

		// �A�C�e���̐������Ԃ̌v�Z����
		mItemExists();

		SetPosition(mPosition);
	}
	// �v���C���[�Ɠ������Ă���
	else if (mCollisionFlag && GetState() != State::Disabling && mItemExistsFlag)
	{
		// �A�C�e�������݂��ĂȂ��Ƃ���
		mItemExistsFlag = false;

		// �X�e�[�g��disabl�ɂ���
		SetState(State::Disabling);

		// �A�C�e���J�E���g�����炷
		ItemBase::mItemCount--;

		// �擾�����A�C�e�����f�[�^�\���Ɋi�[����
		mGetNumber.push_back(mItemNum);
	}

	// �����t���O��false��������
	if (!mItemExistsFlag)
	{
		// �`�����߂�
		mMeshComponent->SetVisible(false);

		// �X�e�[�g��disabl�ɂ���
		SetState(State::Disabling);
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

void Item::mItemType(int _num)
{
	// ���������Ԗڂ��ɂ���Ď�ނ�ς���
	switch (_num)
	{
	case((int)ItemNum::one):
		mItemNum = ItemNum::one;
		mItemExistsTime = MItemExistsOneTime;
		break;
	case((int)ItemNum::two):
		mItemNum = ItemNum::two;
		mItemExistsTime = MItemExistsTwoTime;
		break;
	case((int)ItemNum::three):
		mItemNum = ItemNum::three;
		mItemExistsTime = MItemExistsThreeTime;
		break;
	default:
		break;
	}

}

void Item::mItemExists()
{
	if (mAlpha <= 0.0f && mAlphaDownFlag)
	{
		mAlphaDownFlag = false;
	}
	if (mAlpha >= 1.0f && !mAlphaDownFlag)
	{
		mAlphaDownFlag = true;
	}

	// �A�C�e���̐������Ԃ������Ă�
	mItemExistsTime--;

	// �c��̐������Ԃ�200�����������Ȃ�����
	if (mItemExistsTime <= mItemFlashingTime)
	{
		// �_�ł�����
		if (mAlphaDownFlag)
		{
			mAlpha -= 0.05f;
		}
		else
		{
			mAlpha += 0.05f;
		}
	}

	// �c��̐������Ԃ�0�����������Ȃ�����
	if (mItemExistsTime <= 0)
	{
		// �����t���O��false�ɂ���
		mItemExistsFlag = false;
	}
}
