#pragma once

// �A�C�e���̖��O
enum class itemNames : unsigned char
{
	first,

	cat = first,      // �L
	chair,    // ����
	chara,    // �~�j�L����
	lighter,  // ���C�g
	sword,    // ��
	tree,      // ��

	end
};

// �A�C�e���̃x�[�X�N���X
class ItemBase :public GameObject
{
public:
	// �R���X�g���N�^
	ItemBase(const SceneBase::Scene _sceneTag, const Tag& _objectTag);

	/*
	@fn	�f�X�g���N�^
	*/
	~ItemBase() {};

	// �X�e�[�W�ɂ���A�C�e���̐�
	static int mItemCount;

	// �擾�����A�C�e�����i�[���邽�߂̃f�[�^�\��
	static vector<itemNames> mGetNames;

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
	itemNames mItemName;

	

// �Q�b�^�[�A�Z�b�^�[
public:
	// �擾�����A�C�e�����i�[ @@@ ����Ȃ���
	void SetItemNames(itemNames _itemName) { mGetNames.push_back(_itemName); }
	// �擾�����A�C�e����Ԃ�
	//static const vector<itemNames> GetItemNames() { return mGetNames; }
};

//// �O�u�C���N�������g
//itemNames& operator ++(itemNames& rhs);