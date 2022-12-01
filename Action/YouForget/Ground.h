#pragma once

/*
* ���I�u�W�F�N�g�̏���
*/
class Ground :public GameObject
{
public:
	// ���̎��
	enum class GroundType :unsigned char
	{
		eAlpha,		// �����ɂȂ�
		eNotAlpha,	// �����ɂȂ�Ȃ�
	};

	// ���̐F
	enum class GroundColor :unsigned char
	{
		eRed,		// ��
		eGreen,		// ��
	};

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_pos">�|�W�V����</param>
	/// <param name="_tag">���̎��</param>
	Ground(const Vector3 _pos, const GroundType _tag);
	// �f�X�g���N�^
	~Ground() {};

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="_deltaTime">�Ō�̃t���[������������̂ɗv��������</param>
	void UpdateGameObject(float _deltaTime)override;

	// ���̎�ނ̐��i�V�[���ɂ���ď��̐F�̎�ނ̐����قȂ�j
	static int mTypeNum;

private:
	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�(��������p)
	@param	��������GameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;

	//�Q�[���I�u�W�F�N�g�̃��b�V���|�C���^�ϐ�
	class MeshComponent* mMeshComponent;

	// �l�p�̒n�ʂ̓����蔻��𐶐�
	BoxCollider* mSelfBoxCollider;
	
	// ���l�̕ς���Ă������x
	const float MAlphaAddSpeed;
	const float MAlphaSubSpeed;

	// ���l�̍ő�l
	float MAlphaMax;
	// ���l�̍ŏ��l
	float MAlphaMin;

	// �v���C���[�Ɛڒn���Ă��邩�ǂ���
	bool mIsPlayer;
	// �v���C���[�Ɛڒn���Ă������ǂ���
	bool mBeforeIsPlayer;

	// ���̎��
	const GroundType MGroundType;
	// ���̐F�̎��
	GroundColor mAlphaColorTag;

	// ���̐F�A�����x��ݒ�
	void SetGroundInfo();
};