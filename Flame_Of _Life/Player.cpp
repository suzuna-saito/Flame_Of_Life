/*
@brief	�C���N���[�h
*/
#include "pch.h"


// �萔�ƐÓI�����o�[�̏�����
const float Player::Gravity = 5.0f;

/*
@fn		�R���X�g���N�^
@param	_pos �v���C���[�̍��W
@param	_size �v���C���[�̃T�C�Y
@param	_objectTag �v���C���[�̃^�O
@param	_sceneTag �V�[���̃^�O
*/
Player::Player(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, _objectTag)
	, mIsGroundFlag(false)
	, mNowJump(false)
	, mMoveSpeed(7.0f)
	, mAccelerator(8.0f)
	, mJump(7.0f)
	, mMaxJump(150.0f)
{
	//GameObject�����o�ϐ��̏�����
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	//��������Player�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mMeshComponent = new MeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Player/Candle/Candle_1.gpmesh"));

	//�v���C���[���g�̓����蔻��(�{�b�N�X)
	mSelfBoxCollider = new BoxCollider(this, ColliderTag::playerTag, GetOnCollisionFunc());
	AABB box = { Vector3(3.0f,-3.0f,0.0f),Vector3(-3.0f,3.0f,35.0f) };
	mSelfBoxCollider->SetObjectBox(box);

}

/*
@fn		�v���C���[�̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void Player::UpdateGameObject(float _deltaTime)
{

	//�v���C���[�������낷�ʒu�ɃJ�������Z�b�g
	mMainCamera->SetViewMatrixLerpObject(Vector3(0, -700, 150), mPosition);
	//�v���C���[�������猩��ʒu�ɃJ�������Z�b�g
	//mMainCamera->SetViewMatrixLerpObject(Vector3(300, 0, 200), mPosition);

	// ���W���Z�b�g
	mPosition += mVelocity;

	// �d��
	if (!mIsGroundFlag)
	{
		mPosition.z -= Gravity;
	}

	mIsGroundFlag = false;

	// �|�W�V�������Z�b�g
	SetPosition(mPosition);
}

/*
@fn		���͂������Ŏ󂯎��X�V�֐�
@brief	��{�I�ɂ����œ��͏���ϐ��ɕۑ���UpdateGameObject�ōX�V���s��
@param	_keyState �e���͋@��̓��͏��
@brief	�L�[�{�[�h�A�}�E�X�A�R���g���[���[
*/
void Player::GameObjectInput(const InputState& _keyState)
{
	// W�ŉ��Ɉړ�
	if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W))
	{
		mVelocity.y = mMoveSpeed;
	}
	// S�Ŏ�O�Ɉړ�
	else if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S))
	{
		mVelocity.y = -mMoveSpeed;
	}
	// �ǂ����������Ă��Ȃ���΂����̈ړ����~�߂�
	else
	{
		mVelocity.y = 0.0f;
	}

	// A�ō��Ɉړ�
	if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A))
	{
		mVelocity.x = mMoveSpeed;
	}
	// D�ŉE�Ɉړ�
	else if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D))
	{
		mVelocity.x = -mMoveSpeed;
	}
	// �ǂ����������Ă��Ȃ���΂����̈ړ����~�߂�
	else
	{
		mVelocity.x = 0.0f;
	}


	///// �Ńo�b�N�p //////
	if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_DOWN))
	{
		mVelocity.z = -mMoveSpeed;
	}
	else if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_UP))
	{
		mVelocity.z = mMoveSpeed;
	}
	else
	{
		mVelocity.z = 0.0f;
	}
}

/*
@fn		�v���C���[���q�b�g�������̏���
@param	_hitObject �q�b�g�����Ώۂ̃Q�[���I�u�W�F�N�g�̃A�h���X
*/
void Player::OnCollision(const GameObject& _hitObject)
{
	//�q�b�g�����I�u�W�F�N�g�̃^�O���擾
	mTag = _hitObject.GetTag();

	// ���Ɛݒu������
	if (mTag == ground && mPosition.z >= 50.0f )
	{
		mIsGroundFlag = true;

		mVelocity.z = 0.0f;
	}
}