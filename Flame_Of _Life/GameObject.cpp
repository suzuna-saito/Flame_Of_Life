/*
@brief	�C���N���[�h
*/
#include "pch.h"

//�Q�[���I�u�W�F�N�g��ID�A�J�E���g�p�̏�����
int GameObject::mGameObjectId = 0;
//���C���J�����̏������@������GameObjectManager�������ɍs����
MainCameraObject* GameObject::mMainCamera = nullptr;
//�Q�[���I�u�W�F�N�g�̍X�V���~�߂�C�x���g��Ԃ̏�����
PauzingEvent GameObject::mPauzingEvent = PauzingEvent::NoneEvent;

/*
@param	�Q�[���N���X�̃|�C���^
*/
GameObject::GameObject(SceneBase::Scene _sceneTag, const Tag& _objectTag, bool _reUseGameObject)
	: mState(Active)
	, mWorldTransform()
	, mPosition(Vector3::Zero)
	, mVelocity(Vector3::Zero)
	, mAabb(Vector3::Zero, Vector3::Zero)
	, mScale(Vector3(1.0f, 1.0f, 1.0f))
	, mDirection(Vector3::Zero)
	, mRotation(Quaternion::Identity)
	, mMyObjectId(mGameObjectId)
	, mTag(_objectTag)
	, mSceneTag(_sceneTag)
	, mMoveSpeed(8.0f)
	, MGravity(10.0f)
	, mReUseObject(_reUseGameObject)
	, mRecomputeWorldTransform(true)
	, mHitFlag(false)
	, mRespawnFlag(false)
	, mAlpha(1.0f)
	, mColor(Vector3(1.0f,1.0f,1.0f))
{
	mGameObjectId++;
	//GameObjectManager�Ƀ|�C���^��n��
	GAME_OBJECT_MANAGER->AddGameObject(this);
}

GameObject::~GameObject()
{
	//GameObjectManager����|�C���^���폜����
	GAME_OBJECT_MANAGER->RemoveGameObject(this);
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}

}

/*
@brief	�t���[�����̏���
@param	�Ō�̃t���[������������̂ɗv��������
*/
void GameObject::Update(float _deltaTime)
{
	//�X�V��~�̃C�x���g���łȂ���(�|�[�Y��ʂȂ�)
	if (mPauzingEvent == PauzingEvent::NoneEvent)
	{
		if (mState != Dead)
		{
			//Transform�̃��[���h�ϊ�
			ComputeWorldTransform();
			//�Q�[���I�u�W�F�N�g�̍X�V
			UpdateGameObject(_deltaTime);
			//���̃Q�[���I�u�W�F�N�g�ɕt������R���|�[�l���g�̍X�V
			UpdateComponents(_deltaTime);
			//Transform�̃��[���h�ϊ�
			ComputeWorldTransform();
		}
	}
	//�|�[�Y��ʂ̂Ƃ��R���|�[�l���g���X�V�����Ȃ�(�A�j���[�V�����Ȃǂ��~�߂邽��)
	else if (mPauzingEvent == PauzingEvent::PausingEvent)
	{
		PausingUpdateGameObject();
	}
	else
	{
		PausingUpdateGameObject();
		UpdateComponents(_deltaTime);
	}
}

/*
@brief	�A�^�b�`����Ă�R���|�[�l���g�̃A�b�v�f�[�g
@param	�Ō�̃t���[������������̂ɗv��������
*/
void GameObject::UpdateComponents(float _deltaTime)
{
	if (mState != Dead)
	{
		for (auto itr : mComponents)
		{
			itr->Update(_deltaTime);
		}
	}
}
/*
@brief	�Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
@param	�Ō�̃t���[������������̂ɗv��������
*/
void GameObject::UpdateGameObject(float _deltaTime)
{
}
/*
@fn �Q�[���I�u�W�F�N�g���Î~���ɍX�V�����A�b�v�f�[�g�֐�
@brief pauzingUpdate��true�̂Ƃ������Ă΂��X�V�֐�
*/
void GameObject::PausingUpdateGameObject()
{
}

/*
@fn ���͏�Ԃ��󂯎��GameObject��Component�̓��͍X�V�֐����Ăяo��
*/
void GameObject::ProcessInput(const InputState& _keyState)
{
	if (mState == Active)
	{
		//�R���|�[�l���g�̓��͊֐��ɃR���g���[���[�̓��͏�Ԃ�
		for (auto comp : mComponents)
		{
			comp->ProcessInput(_keyState);
		}
		//�Q�[���I�u�W�F�N�g�̓��͊֐��ɃR���g���[���[�̓��͏�Ԃ�
		GameObjectInput(_keyState);
	}
}

/*
@fn ���͂������Ŏ󂯎��X�V�֐�
@brief ��{�I�ɂ����œ��͏���ϐ��ɕۑ���UpdateGameObject�ōX�V���s��
*/
void GameObject::GameObjectInput(const InputState& _keyState)
{
}

/*
@brief	�R���|�[�l���g��ǉ�����
@param	�ǉ�����R���|�[�l���g�̃|�C���^
*/
void GameObject::AddComponent(Component* _component)
{
	int order = _component->GetUpdateOder();
	auto itr = mComponents.begin();
	for (;
		itr != mComponents.end();
		++itr)
	{
		if (order < (*itr)->GetUpdateOder())
		{
			break;
		}
	}
	mComponents.insert(itr, _component);
}

/*
@brief	�R���|�[�l���g���폜����
@param	�폜����R���|�[�l���g�̃|�C���^
*/
void GameObject::RemoveComponent(Component* _component)
{
	auto itr = std::find(mComponents.begin(), mComponents.end(), _component);
	if (itr != mComponents.end())
	{
		mComponents.erase(itr);
	}
}
/*
@fn ���݂̎d�l��s�����Ƃ��ł��Ȃ��������O�����狭���ɍs�����߂̊֐�
@exsample �Q�[���I�u�W�F�N�g�S�̂̍X�V����~���ɑΏۂ̃Q�[���I�u�W�F�N�g���X�V����
*/
void GameObject::ExceptionUpdate()
{
	ComputeWorldTransform();

	UpdateGameObject(0.016f);
	UpdateComponents(0.016f);

	ComputeWorldTransform();
}


/*
@brief	Transform�̃��[���h�ϊ�
*/
void GameObject::ComputeWorldTransform()
{
	//���[���h�ϊ����K�v���ǂ����H
	//�����K�v�������烏�[���h�ϊ����s��
	if (mRecomputeWorldTransform)
	{
		//object��
		//�ϊ����K�v�t���O���~�낷
		mRecomputeWorldTransform = false;
		//�X�P�[���̃��[���h�ϊ�
		mWorldTransform = Matrix4::CreateScale(mScale);
		//��]�̃��[���h�ϊ��i�N�E�H�[�^�j�I���j
		mWorldTransform *= Matrix4::CreateFromQuaternion(mRotation);
		//���s�ړ��̍X�V
		mWorldTransform *= Matrix4::CreateTranslation(mPosition);

		//object�iowner�j�������Ă���component�ɂ����W�ϊ��n
		for (auto itr : mComponents)
		{
			itr->OnUpdateWorldTransform();
		}
	}
}

void GameObject::FixCollision(const AABB& _myAABB, const AABB& _pairAABB, const Tag& _pairTag)
{
	Vector3 ment = Vector3(0, 0, 0);
	CalcCollisionFixVec(_myAABB, _pairAABB, ment);
	SetPosition(GetPosition() + (ment));
}

void GameObject::CreateMainCamera()
{
	mMainCamera = new MainCameraObject();
}

void GameObject::CalcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec)
{
	_calcFixVec = Vector3(0, 0, 0);
	float dx1 = _fixedBox.m_min.x - _movableBox.m_max.x;
	float dx2 = _fixedBox.m_max.x - _movableBox.m_min.x;
	float dy1 = _fixedBox.m_min.y - _movableBox.m_max.y;
	float dy2 = _fixedBox.m_max.y - _movableBox.m_min.y;
	float dz1 = _fixedBox.m_min.z - _movableBox.m_max.z;
	float dz2 = _fixedBox.m_max.z - _movableBox.m_min.z;

	// dx, dy, dz �ɂ� ���ꂼ��1,2�̂�����Βl�������������Z�b�g����
	float dx = (Math::Abs(dx1) < Math::Abs(dx2)) ? dx1 : dx2;
	float dy = (Math::Abs(dy1) < Math::Abs(dy2)) ? dy1 : dy2;
	float dz = (Math::Abs(dz1) < Math::Abs(dz2)) ? dz1 : dz2;

	// x, y, z�̂����ł��������������ňʒu�𒲐�
	if (Math::Abs(dx) <= Math::Abs(dy) && Math::Abs(dx) <= Math::Abs(dz))
	{
		_calcFixVec.x = dx;
	}
	else if (Math::Abs(dy) <= Math::Abs(dx) && Math::Abs(dy) <= Math::Abs(dz))
	{
		_calcFixVec.y = dy;
	}
	else
	{
		_calcFixVec.z = dz;
	}
}

/*
@fn		�O���x�N�g���̌����ɉ�]����
@param	_forward �����������O�������x�N�g��
*/
void GameObject::RotateToNewForward(const Vector3& _forward)
{
	// X���x�N�g��(1,0,0)��forward�̊Ԃ̊p�x�����߂�
	float dot = Vector3::Dot(Vector3::UnitX, _forward);
	float angle = Math::Acos(dot);
	//printf("%f\n", angle);
	// �������������ꍇ
	if (dot > 0.9999f)
	{
		SetRotation(Quaternion::Identity);
	}
	// ������������ꍇ
	else if (dot < -0.9999f)
	{
		SetRotation(Quaternion(Vector3::UnitZ, Math::Pi));
	}
	else
	{
		// ���x�N�g����forward�Ƃ̊O�ς����]�������Ƃ߁A��]������
		Vector3 axis = Vector3::Cross(Vector3::UnitX, _forward);
		axis.Normalize();
		SetRotation(Quaternion(axis, angle));
	}
}
