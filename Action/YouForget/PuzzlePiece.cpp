#include "pch.h"

// �ÓI�����o�ϐ��̏�����
vector<PuzzlePiece::PieceNum> PuzzlePiece::mGetNumber;	// ���W�����s�[�X�̊i�[

PuzzlePiece::PuzzlePiece(const Vector3 _pos, const int _num)
	: GameObject(ObjTag::ePuzzle)
	, mPieceNum()
	, MMaxPos(_pos.z + 70.0f)
	, MMinPos(_pos.z)
	, mAlphaMove(0.05f)
	, mPosMove(70.0f)
	, mPieceExistsTime(0)
	, mPieceFlashingTime(200)
	, mPieceExistsFlag(true)
{
	// MeshComponent�𐶐����邱�ƂŎ����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mMeshComponent = new MeshComponent(this);
	// Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Item/Puzzle.gpmesh"));

	// �����蔻��
	mSelfBoxCollider = new BoxCollider(this, mTag, GetOnCollisionFunc());
	AABB box = { Vector3(-3.0f,-3.0f,-3.0f),Vector3(3.0f,4.0f,3.0f) };
	mSelfBoxCollider->SetObjectBox(box);

	// ��]����						����]����l
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

	// GameObject�����o�ϐ��̏�����
	SetScale(Vector3(18.0f, 18.0f, 18.0f));	// �X�P�[��
	SetPosition(_pos);						// �|�W�V����
	mColor = Vector3(0.68f, 0.85f, 1.2f);	// �F

	// �p�Y���s�[�X�̊ۉe�G�t�F�N�g�𐶐�
	new CircledShadow(this, Color::LightBlue);

	// �p�Y���s�[�X�̃i���o�[�A�������Ԃ�ݒ�
	SetPieceInfo(_num);
}

void PuzzlePiece::SetPieceInfo(int _num)
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
	else if (SceneBase::mIsSceneType == SceneBase::SceneType::eThird)
	{
		MItemExistsOneTime = 4800;
		MItemExistsTwoTime = 3600;
		MItemExistsThreeTime = 1600;
	}

	// ���������Ԗڂ���ۑ��A�������Ԃ���
	if (_num == (int)PieceNum::eOne)
	{
		mPieceNum = PieceNum::eOne;
		mPieceExistsTime = MItemExistsOneTime;
	}
	else if (_num == (int)PieceNum::eTwo)
	{
		mPieceNum = PieceNum::eTwo;
		mPieceExistsTime = MItemExistsTwoTime;
	}
	else
	{
		mPieceNum = PieceNum::eThree;
		mPieceExistsTime = MItemExistsThreeTime;
	}
}

void PuzzlePiece::UpdateGameObject(float _deltaTime)
{
	// �p�Y���s�[�X�̐������Ԃ̌v�Z
	PieceExists();

	// �����t���O��false��������
	if (!mPieceExistsFlag)
	{
		// �`�����߂�
		mMeshComponent->SetVisible(false);

		// �X�e�[�g���X�V��~��Ԃɂ���
		SetState(State::Paused);

		return;
	}

	// �v���C���[�Ɠ���������
	if (mCollisionFlag)
	{
		// �擾�����p�Y���s�[�X���f�[�^�\���Ɋi�[����
		mGetNumber.push_back(mPieceNum);

		// �p�Y���s�[�X�����݂��ĂȂ��Ƃ���
		mPieceExistsFlag = false;
	}
	else
	{
		// �p�Y���s�[�X���㉺������
		mPosition.z += mPosMove * _deltaTime;

		// �|�W�V�������ݒ肵���ő�l�ȏ�܂��́A�ŏ��l�ȉ��ɂȂ�����
		if (mPosition.z >= MMaxPos || mPosition.z <= MMinPos)
		{
			// �ړ��l�̕����𔽓]������
			mPosMove *= -1;
		}

		// �|�W�V�������X�V
		SetPosition(mPosition);
	}
}

void PuzzlePiece::OnCollision(const GameObject& _hitObject)
{
	// �v���C���[������\��Ԃ̎��Ƀs�[�X�ɓ���������
	if (Player::mOperable)
	{
		// ���������̂Ńt���O���グ��
		mCollisionFlag = true;
	}
}

void PuzzlePiece::PieceExists()
{
	// �p�Y���s�[�X�̐������Ԃ������Ă�
	--mPieceExistsTime;

	// �c��̐������Ԃ�0�����������Ȃ�����A���A���l��0�ȉ��ɂȂ�����
	if (mPieceExistsTime <= 0 && mAlpha <= 0.0f)
	{
		// �����t���O��false�ɂ���
		mPieceExistsFlag = false;
		return;
	}

	// �c��̐������Ԃ��ݒ肵���l�����������Ȃ�����A�_�ł�����
	if (mPieceExistsTime <= mPieceFlashingTime)
	{
		mAlpha += mAlphaMove;

		// ���l��1�ȏ�A�܂���0�ȉ���������
		if (mAlpha >= 1.0f || mAlpha <= 0.0f)
		{
			// ���l�̕ω��l�̕�����ύX
			mAlphaMove *= -1;
		}
	}
}