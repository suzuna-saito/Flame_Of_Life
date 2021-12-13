#pragma once

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

	static int mItemCount;

protected:
	//�Q�[���I�u�W�F�N�g�̃��b�V���|�C���^�ϐ�
	MeshComponent* mMeshComponent;

	// �l�p�̓����蔻��𐶐�
	BoxCollider* mSelfBoxCollider;

	// �v���C���[�Ɠ����������ǂ����̔���
	bool mCollisionFlag;
private:
};

