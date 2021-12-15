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

protected:
	//�Q�[���I�u�W�F�N�g�̃��b�V���|�C���^�ϐ�
	MeshComponent* mMeshComponent;

	// �l�p�̓����蔻��𐶐�
	BoxCollider* mSelfBoxCollider;

	// �v���C���[�Ɠ����������ǂ����̔���
	bool mCollisionFlag;
private:
	// �擾�����A�C�e�����i�[���邽�߂̃f�[�^�\��
	vector<itemNames> mNames;

// �Q�b�^�[�A�Z�b�^�[
public:
	// �擾�����A�C�e�����i�[
	void SetItemNames(itemNames _itemName) { mNames.push_back(_itemName); }

	const vector<itemNames> GetItemNames() const { return mNames; }
};

//// �O�u�C���N�������g
//itemNames& operator ++(itemNames& rhs);