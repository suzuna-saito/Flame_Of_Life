#pragma once

class SwitchCollider;

// �X�C�b�`�̃I�u�W�F�N�g
class Switch :public GameObject
{
public:

	// �X�C�b�`�̐F
	enum class switchColor :unsigned char
	{
		red,
		green,
		yellow,
	};

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_pos">�|�W�V����</param>
	/// <param name="_size">�T�C�Y</param>
	/// <param name="_objectTag">���g�̃^�O</param>
	/// <param name="_sceneTag">���݂̃V�[���^�O</param>
	/// <param name="_color">�����������F�̎��</param>
	Switch(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag, const switchColor& _color);

	/*
	@fn	�f�X�g���N�^
	*/
	~Switch() {};

	// �X�V
	void UpdateGameObject(float _deltaTime)override;

	// �X�C�b�`�������Ă��邩�̃t���O
	static bool mSwitchFlag;

	// �X�C�b�`�̐F
	switchColor mSwitchColor;
private:

	//�Q�[���I�u�W�F�N�g�̃��b�V���|�C���^�ϐ�
	MeshComponent* mMeshComponent;

	// �l�p�̒n�ʂ̓����蔻��𐶐�
	BoxCollider* mSelfBoxCollider;

	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
	@param	��������GameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;

	// �X�C�b�`���S�̓����蔻��
	SwitchCollider* mSwitchCenter;

public: // �Q�b�^�[�A�Z�b�^�[
	// �X�C�b�`�̐F��Ԃ�
	switchColor GetSwitchColor() { return mSwitchColor; }
};

