/*
@brief	�v���v���Z�b�T
*/
#pragma once

class Component;
class ColliderComponent;
class MeshComponent;
class Mesh;
class BoxCollider;

/*
@enum	GameObject�X�e�[�g
@brief	�Q�[���I�u�W�F�N�g�̏��
*/
enum class State :unsigned char
{
	//�A�N�e�B�u
	Active,
	//�X�V����~���Ă���
	Paused,
	//�I�u�W�F�N�g�̍X�V���I��(�O������̂�Active�ɕύX�\)
	Dead,
};

/*
@enum	GameObject�^�O
@brief	�Փˑ���𔻕ʂ��邽�߂Ɏg�p
*/
enum class Tag :unsigned char
{
	NoCollision,
	Camera,
	player,
	playerLegs,
	ground,
	candle,
	Switch,
	SwitchCenter,
	item,
};

/*
@enum	�Q�[���I�u�W�F�N�g�̍X�V���~����C�x���g��
*/
enum class PauzingEvent :unsigned char
{
	//�|�[�Y��ʒ�
	PausingEvent,
	//�v���C���[�����j����Ă��܂����ۂ̉��o
	DeadPlayerEvent,
	//�Q�[���I�[�o�[���̉��o DeadPlayerEvent�Ɗ֘A
	GameOverEvent,
	//�Q�[���I�u�W�F�N�g�̍X�V���s���Ă���B
	NoneEvent
};

class GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_sceneTag �V�[���̃^�O
	@param	_objectTag �Q�[���I�u�W�F�N�g�̃^�O
	@param	_reUseGameObject
	*/
	GameObject(const SceneBase::SceneType _sceneTag, const Tag& _objectTag = Tag::NoCollision, bool _reUseGameObject = false);

	/*
	@fn	�f�X�g���N�^
	*/
	virtual ~GameObject();

	/*
	@fn		�t���[�����̏���
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void Update(float _deltaTime);

	/*
	@fn		�A�^�b�`����Ă�R���|�[�l���g�̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateComponents(float _deltaTime);

	/*
	@fn		�Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	virtual void UpdateGameObject(float _deltaTime);

	/*
	@fn		�Q�[���I�u�W�F�N�g���Î~���ɍX�V�����A�b�v�f�[�g�֐�
	@brief	pauzingUpdate��true�̂Ƃ������Ă΂��X�V�֐�
	*/
	virtual void PausingUpdateGameObject();

	/*
	@fn		���͏�Ԃ��󂯎��GameObject��Component�̓��͍X�V�֐����Ăяo��
	@param	_keyState �e���͋@��̓��͏��
	@brief	�L�[�{�[�h�A�}�E�X�A�R���g���[���[
	*/
	void ProcessInput(const InputState& _keyState);

	/*
	@fn		���͂������Ŏ󂯎��X�V�֐�
	@brief	��{�I�ɂ����œ��͏���ϐ��ɕۑ���UpdateGameObject�ōX�V���s��
	@param	_keyState �e���͋@��̓��͏��
	@brief	�L�[�{�[�h�A�}�E�X�A�R���g���[���[
	*/
	virtual void GameObjectInput(const InputState& _keyState);

	/*
	@fn		�R���|�[�l���g��ǉ�����
	@param	_component �ǉ�����R���|�[�l���g�̃|�C���^
	*/
	void AddComponent(Component* _component);

	/*
	@fn		�R���|�[�l���g���폜����
	@param	_component �폜����R���|�[�l���g�̃|�C���^
	*/
	void RemoveComponent(Component* _component);

	/*
	@fn			���݂̎d�l��s�����Ƃ��ł��Ȃ��������O�����狭���ɍs�����߂̊֐�
	@exsample	�Q�[���I�u�W�F�N�g�S�̂̍X�V����~���ɑΏۂ̃Q�[���I�u�W�F�N�g���X�V����
	*/
	void ExceptionUpdate();

	/*
	@fn	Transform�̃��[���h�ϊ�
	*/
	void ComputeWorldTransform();

	/*
	@fn		��`�Ƌ�`�̉����߂�
	@param	_myAABB	��ɂ���I�u�W�F�N�g�̋�`�����蔻��
	@param	_pairAABB �q�b�g����I�u�W�F�N�g�̋�`�����蔻��
	@param	_pairTag �q�b�g����I�u�W�F�N�g�̃^�O
	*/
	virtual void FixCollision(const AABB& _myAABB, const AABB& _pairAABB, const Tag& _pairTag);

	/*
	@fn		�O���x�N�g���̌����ɉ�]����
	@param	_forward �����������O�������x�N�g��
	*/
	void RotateToNewForward(const Vector3& _forward);

	/*
	@fn �ÓI��mainCamera�𐶐�����
	*/
	static void CreateMainCamera();

protected:

	/*
	@fn �Փ˂������Ƃ��m�肵���Ƃ��A�߂荞�݂�߂��֐�
	@param _movableBox �ړ�����
	@param _fixedBox �ړ����Ȃ�����
	@param _calcFixVec �ړ����̂̕␳�����x�N�g��
	*/
	void CalcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec);

	//function<void(GameObject&, AABB, AABB)> GetOnCollisionFunc() { return bind(&GameObject::OnCollision, this, placeholders::_1, placeholders::_2, placeholders::_3); }
	function<void(GameObject&)> GetOnCollisionFunc() { return bind(&GameObject::OnCollision, this, placeholders::_1); }
	/*
	@fn		�Q�[���I�u�W�F�N�g���q�b�g�������̏���
	@param	_hitObject �q�b�g�����Ώۂ̃Q�[���I�u�W�F�N�g�̃A�h���X
	*/
	virtual void OnCollision(const GameObject& _hitObject) {}

	//virtual void OnCollision(const GameObject& _hitObject,const AABB _movableBox, const AABB _fixedBox) {}

	//���C���J�����@������GameObjectManager�������ɍs����
	static class MainCameraObject* mMainCamera;
	//�Q�[���I�u�W�F�N�g�̍X�V���~�߂�C�x���g���
	static PauzingEvent mPauzingEvent;
	//�Փˎ��̃��A�N�V�����֐�(ColliderComponent�ɂ��̊֐��̃A�h���X��n��) Enter...�Փ˂��� Stay...�Փ˂��Ă���
	virtual void OnTriggerEnter(ColliderComponent* _colliderPair) {};
	//�Փˎ��̃��A�N�V�����֐�(ColliderComponent�ɂ��̊֐��̃A�h���X��n��) Enter...�Փ˂��� Stay...�Փ˂��Ă���
	virtual void OnTriggerStay(ColliderComponent* _colliderPair) {};

	//�I�u�W�F�N�g��AABB
	AABB mAabb;
	//�Q�[���I�u�W�F�N�g�̏��
	State mState;
	//�Q�[���I�u�W�F�N�g�̃^�O
	Tag mTag;
	//�Q�[���I�u�W�F�N�g��ID�A�J�E���g�p
	static int mGameObjectId;
	//���̃Q�[���I�u�W�F�N�g��ID
	int mMyObjectId;

	// �{�b�N�X�̓����蔻��
	BoxCollider* mBoxCollider;

	//Transform
	Vector3 mPosition;
	Vector3 mVelocity;
	Vector3 mInputSpeed;
	Vector3 mScale;
	Vector3 mDirection;
	Vector3 mForwardVec;
	//�I�u�W�F�N�g�̃N�H�[�^�j�I��
	Quaternion  mRotation;
	//�I�u�W�F�N�g�̃��[���h�s��
	Matrix4	mWorldTransform;
	//�ړ����x
	float mMoveSpeed;
	//�d��
	float mGravity;
	//���[���h�ϊ��̏������s���K�v�������邩
	bool mRecomputeWorldTransform;
	// ���X�|�[��������
	bool mRespawnFlag;

	// ���l
	float mAlpha;
	Vector3 mColor;

	//�V�[���̃^�O
	SceneBase::SceneType mSceneTag;
	//�A�^�b�`����Ă���R���|�[�l���g
	vector<class Component*>mComponents;
private:

	//�V�[�����ׂ��ۂɉ�������I�u�W�F�N�g���ǂ����A�J�����Ȃǂ��ΏۂɂȂ�
	bool mReUseObject;

public://�Q�b�^�[�Z�b�^�[

	float GetAlpha() { return mAlpha; }
	Vector3 GetColor()const { return mColor; }

	/*
	@return	�I�u�W�F�N�g�̃|�W�V����(Vector3�^)
	*/
	const Vector3& GetPosition() const { return mPosition; }

	/*
	@return	�I�u�W�F�N�g�̑��x(Vector3�^)
	*/
	const Vector3& GetVelocity() const { return mVelocity; }

	/*
	@return	���[���h�ϊ��̏������s���K�v�������邩�̃t���O(bool�^)
	*/
	bool GetRecomputeWorldTransform() { return mRecomputeWorldTransform; }

	/*
	@return	�I�u�W�F�N�g�̃X�P�[��(float�^)
	*/
	float GetScale() const { return mScale.x; }

	/*
	@return	�I�u�W�F�N�g�̃N�H�[�^�j�I��(Quaternion�^)
	*/
	const Quaternion& GetRotation() const { return mRotation; }

	/*
	@return	�I�u�W�F�N�g�̏��(enum�^ State)
	*/
	State GetState() const { return mState; }

	/*
	@return	�I�u�W�F�N�g�̃��[���h�s��(Matrix4�^)
	*/
	const Matrix4& GetWorldTransform() const { return mWorldTransform; }

	/*
	@return	�I�u�W�F�N�g�̑O����\���x�N�g��(Vector3�^)
	*/
	Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitZ, mRotation); }

	/*
	@return	�I�u�W�F�N�g�̉E��\���x�N�g��(Vector3�^)
	*/
	Vector3 GetRight() const { return Vector3::Transform(Vector3::UnitX, mRotation); }

	/*
	@return	�I�u�W�F�N�g�̏��\���x�N�g��(Vector3�^)
	*/
	Vector3 GetUp() const { return Vector3::Transform(Vector3::UnitY, mRotation); };

	/*
	@return	�I�u�W�F�N�g�̃^�O(enum�^ Tag)
	*/
	Tag GetTag() const { return mTag; };

	/*
	@return	�I�u�W�F�N�g��id(int�^)
	*/
	int GetObjectId() { return mMyObjectId; };

	/*
	@return	��������I�u�W�F�N�g(bool�^)
	*/
	bool GetReUseGameObject() { return mReUseObject; };

	/*
	@return	�V�[���̃^�O
	*/
	SceneBase::SceneType GetScene() { return mSceneTag; };

	/*
	@return	�I�u�W�F�N�g��AABB
	*/
	AABB GetObjectAABB() { return mAabb; };

	/*
	@param	_scale �I�u�W�F�N�g�̃X�P�[��
	*/
	void SetScale(Vector3 _scale) { mScale.x = _scale.x; mScale.y = _scale.y; mScale.z = _scale.z; mRecomputeWorldTransform = true; }

	/*
	@param	_qotation �I�u�W�F�N�g�̃N�H�[�^�j�I��
	*/
	virtual void SetRotation(const Quaternion& _qotation) { mRotation = _qotation;  mRecomputeWorldTransform = true; }

	/*
	@param	_state �I�u�W�F�N�g�̏��
	*/
	virtual void SetState(State _state) { mState = _state; }

	/*
	@param	_pos �I�u�W�F�N�g�̃|�W�V����
	*/
	virtual void SetPosition(const Vector3& _pos) { mPosition = _pos; mRecomputeWorldTransform = true; }

	AABB GetAabb() const { return mAabb; }

};

