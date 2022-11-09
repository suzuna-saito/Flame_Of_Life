#pragma once

// �X�C�b�`�̃I�u�W�F�N�g
class Switch :public GameObject
{
public:
	// �X�C�b�`�̐F
	enum class switchColor :unsigned char
	{
		red,	// ��
		green,	// ��
	};

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_pos">�|�W�V����</param>
	/// <param name="_color">�����������F�̎��<</param>
	Switch(const Vector3 _pos, const switchColor& _color);
	// �f�X�g���N�^
	~Switch() {};

	// �X�V
	void UpdateGameObject(float _deltaTime)override;

	// �X�C�b�`�������Ă��邩�̃t���O
	static bool mFollowSwitchFlag;

private:

	//�Q�[���I�u�W�F�N�g�̃��b�V���|�C���^�ϐ�
	MeshComponent* mMeshComponent;

	// �l�p�̒n�ʂ̓����蔻��𐶐�
	BoxCollider* mSelfBoxCollider;

	// �X�C�b�`���S�̓����蔻��
	class SwitchCollider* mSwitchCenter;
};