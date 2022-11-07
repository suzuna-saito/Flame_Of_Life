#include "pch.h"

// �ÓI�����o�ϐ��̏�����
vector<Item::PieceNum> Item::mGetNumber;	// ���W�����s�[�X�̊i�[

Item::Item(const Vector3 _pos, const int _num)
	: GameObject(ObjTag::ePuzzle)
	, mItemExistsTime(0)
	, mItemFlashingTime(200)
	, mItemExistsFlag(true)
	, MMaxPos(_pos.z + 70.0f)
	, MMinPos(_pos.z)
	, mPosMove(70.0f)
	, mAlphaMove(0.05f)
{
	// Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mMeshComponent = new MeshComponent(this);
	// Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Item/Puzzle.gpmesh"));

	//�����蔻��
	mSelfBoxCollider = new BoxCollider(this, mTag, GetOnCollisionFunc());
	AABB box = { Vector3(3.0f,-3.0f,-3.0f),Vector3(-3.0f,4.0f,3.0f) };
	mSelfBoxCollider->SetObjectBox(box);

	//��]����                        ����]����l
	float radianZ = Math::ToRadians(90.0f);					// Z����]
	Quaternion rot = this->GetRotation();
	Quaternion incZ(Vector3::UnitZ, radianZ);
	Quaternion target = Quaternion::Concatenate(rot, incZ);
	SetRotation(target);

	float radianY = Math::ToRadians(-80.0f * (int)_num);	// Y����]
	rot = this->GetRotation();
	Quaternion incY(Vector3::UnitY, radianY);
	target = Quaternion::Concatenate(rot, incY);
	SetRotation(target);

	float radianX = Math::ToRadians(-40.0f);				// X����]
	rot = this->GetRotation();
	Quaternion incX(Vector3::UnitX, radianX);
	target = Quaternion::Concatenate(rot, incX);
	SetRotation(target);

	//GameObject�����o�ϐ��̏�����
	SetScale(Vector3(18.0f, 18.0f, 18.0f));	// �X�P�[��
	SetPosition(_pos);						// �|�W�V����
	mColor = Vector3(0.68f, 0.85f, 1.2f);	// �F

	// �A�C�e���̊ۉe�G�t�F�N�g�𐶐�
	new CircledShadow(this, Color::LightBlue);

	// �p�Y���s�[�X�̃i���o�[�A�������Ԃ�ݒ�
	SetPieceInfo(_num);
}

void Item::SetPieceInfo(int _num)
{
	// �������ꂽ�Ƃ��̃V�[���ɂ���ăp�Y���s�[�X�̐������Ԃ�ς���
	int MItemExistsOneTime = 0;
	int MItemExistsTwoTime = 0;
	int MItemExistsThreeTime = 0;

	if (SceneBase::mIsSceneType == SceneBase::SceneType::eFirst)
	{
		MItemExistsOneTime = 2000;		// ��ԉ��̃s�[�X
		MItemExistsTwoTime = 1700;		// �^�񒆂̃s�[�X
		MItemExistsThreeTime = 1000;	// ��ԋ߂��̃s�[�X
	}
	else if (SceneBase::mIsSceneType == SceneBase::SceneType::eSecond)
	{
		MItemExistsOneTime = 2700;
		MItemExistsTwoTime = 800;
		MItemExistsThreeTime = 600;
	}
	else if(SceneBase::mIsSceneType == SceneBase::SceneType::eThird)
	{
		MItemExistsOneTime = 4800;
		MItemExistsTwoTime = 3600;
		MItemExistsThreeTime = 1600;
	}

	// ���������Ԗڂ���ۑ��A�������Ԃ���
	if (_num == (int)PieceNum::one)
	{
		mItemNum = PieceNum::one;
		mItemExistsTime = MItemExistsOneTime;
	}
	else if (_num == (int)PieceNum::two)
	{
		mItemNum = PieceNum::two;
		mItemExistsTime = MItemExistsTwoTime;
	}
	else
	{
		mItemNum = PieceNum::three;
		mItemExistsTime = MItemExistsThreeTime;
	}
}

void Item::UpdateGameObject(float _deltaTime)
{
	// �p�Y���s�[�X�̐������Ԃ̌v�Z
	PieceExists();

	// �����t���O��false��������
	if (!mItemExistsFlag)
	{
		// �`�����߂�
		mMeshComponent->SetVisible(false);

		// �X�e�[�g���X�V��~��Ԃɂ���
		SetState(State::Paused);
	}
	// �܂��s�[�X���������Ă��鎞�Ƀv���C���[�Ɠ���������
	else if (mCollisionFlag)
	{
		// �擾�����A�C�e�����f�[�^�\���Ɋi�[����
		mGetNumber.push_back(mItemNum);

		// �A�C�e�������݂��ĂȂ��Ƃ���
		mItemExistsFlag = false;
	}
	else
	{
		// �p�Y���s�[�X���㉺������
		mPosition.z += mPosMove * _deltaTime;

		// �|�W�V�������ݒ肵���ő�l�ȏ�܂��́A�ŏ��l�����ɂȂ�����
		if (mPosition.z >= MMaxPos || mPosition.z <= MMinPos)
		{
			// �ړ��l�̕����𔽓]������
			mPosMove *= -1;
		}

		// �|�W�V�������X�V
		SetPosition(mPosition);
	}
}

void Item::OnCollision(const GameObject& _hitObject)
{
	// �v���C���[������\��Ԃ̎��Ƀs�[�X�ɓ���������
	if (Player::mOperable)
	{
		// ���������̂Ńt���O���グ��
		mCollisionFlag = true;
	}
}

void Item::PieceExists()
{
	// �A�C�e���̐������Ԃ������Ă�
	mItemExistsTime--;

	// �c��̐������Ԃ�200�����������Ȃ�����
	if (mItemExistsTime <= mItemFlashingTime)
	{
		// �_�ł�����
		mAlpha += mAlphaMove;

		// ���l��1�ȏ�A�܂���0�ȉ���������
		if (mAlpha >= 1.0f || mAlpha <= 0.0f)
		{
			// ���l�̕ω��l�̕�����ύX
			mAlphaMove *= -1;
		}
	}

	// �c��̐������Ԃ�0�����������Ȃ�����A���A���l��0�ȉ��ɂȂ�����
	if (mItemExistsTime <= 0 && mAlpha <= 0.0f)
	{
		// �����t���O��false�ɂ���
		mItemExistsFlag = false;
	}
}