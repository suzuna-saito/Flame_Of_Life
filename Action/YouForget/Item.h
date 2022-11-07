#pragma once

/*
* �p�Y���s�[�X�i���W���j�̏���
*/
class Item :public GameObject
{
public:
	// �p�Y���s�[�X�̃i���o�[
	enum class PieceNum : unsigned char
	{
		one,
		two,
		three,
	};

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_pos">�|�W�V����</param>
	/// <param name="_num">���ڂ̃s�[�X��</param>
	Item(const Vector3 _pos, const int _num);
	// �f�X�g���N�^
	~Item() {};

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="_deltaTime">�Ō�̃t���[������������̂ɗv��������</param>
	void UpdateGameObject(float _deltaTime)override;

	// ���W�����p�Y���s�[�X���i�[���邽�߂̃f�[�^�\��
	static vector<PieceNum> mGetNumber;

private:
	/// <summary>
	/// �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
	/// </summary>
	/// <param name="_hitObject">Hit�����Ώۂ̃Q�[���I�u�W�F�N�g�̃A�h���X</param>
	void OnCollision(const GameObject& _hitObject)override;

	/// <summary>
	/// �p�Y���s�[�X�̃i���o�[�A�������Ԃ�ݒ�
	/// </summary>
	/// <param name="_num">�s�[�X�̐����ԍ�</param>
	void SetPieceInfo(int _num);
	// �p�Y���s�[�X�̐������Ԃ̌v�Z
	void PieceExists();

	// �Q�[���I�u�W�F�N�g�̃��b�V���|�C���^�ϐ�
	class MeshComponent* mMeshComponent;
	// �l�p�̓����蔻��𐶐�
	class BoxCollider* mSelfBoxCollider;

	// �s�[�X�̏㉺�ړ�pos�l
	const float MMaxPos;	// �ő�l
	const float MMinPos;	// �ŏ��l

	PieceNum mItemNum;		// �s�[�X�̎��

	int mItemExistsTime;	// �s�[�X�̂��ꂼ��̐�������
	int mItemFlashingTime;	// �s�[�X���_�ł��n�߂鎞��

	float mPosMove;			// �|�W�V�����̈ړ��l
	float mAlphaMove;		// ���l�̕ύX�l

	bool mItemExistsFlag;	// �s�[�X���܂����݂��Ă��邩�̃t���O true _���݂��� false _���݂��Ȃ�
	bool mCollisionFlag;	// �v���C���[�Ɠ����������ǂ����̔���
};