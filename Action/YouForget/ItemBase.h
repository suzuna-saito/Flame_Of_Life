#pragma once

// �A�C�e���̃i���o�[
enum class ItemNum : unsigned char
{
	first,

	one = first,
	two,
	three,

	end
};

// �A�C�e���̃x�[�X�N���X
class ItemBase :public GameObject
{
public:
	// �R���X�g���N�^
	ItemBase(const SceneBase::SceneType _sceneTag, const ObjTag& _objectTag);

	/*
	@fn	�f�X�g���N�^
	*/
	~ItemBase() {};

	// �X�e�[�W�ɂ���A�C�e���̐�
	static int mItemCount;

	// �擾�����A�C�e�����i�[���邽�߂̃f�[�^�\��
	static vector<ItemNum> mGetNumber;

protected:
	//�Q�[���I�u�W�F�N�g�̃��b�V���|�C���^�ϐ�
	MeshComponent* mMeshComponent;

	// �l�p�̓����蔻��𐶐�
	BoxCollider* mSelfBoxCollider;

	// �A�C�e���̓���
	float mMove;
	float mMaxMove;
	float mMinMove;
	bool mUpFlag;

	// �v���C���[�Ɠ����������ǂ����̔���
	bool mCollisionFlag;

	// �A�C�e���̎��
	ItemNum mItemNum;

	

// �Q�b�^�[�A�Z�b�^�[
public:
	// �擾�����A�C�e�����i�[
	//void SetItemNames(ItemNum _itemName) { mGetNames.push_back(_itemName); }
};

//// �O�u�C���N�������g
//ItemNum& operator ++(ItemNum& rhs);