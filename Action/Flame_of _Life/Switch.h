#pragma once

// ���̂̃I�u�W�F�N�g
class Switch :public GameObject
{
public:

	// �R���X�g���N�^
	Switch(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag, const Ground::alphaColor& _tag);

	/*
	@fn	�f�X�g���N�^
	*/
	~Switch() {};

	// �X�V
	void UpdateGameObject(float _deltaTime)override;

	// �X�C�b�`�������Ă��邩�̃t���O
	static bool mSwitchFlag;
private:

	//�Q�[���I�u�W�F�N�g�̃��b�V���|�C���^�ϐ�
	MeshComponent* mMeshComponent;

	// �l�p�̒n�ʂ̓����蔻��𐶐�
	BoxCollider* mSelfBoxCollider;

	// �v���C���[�ƃX�C�b�`�̋���
	static float mDistance;

	// �X�C�b�`�ƘA�g���Ă��鏰�̐F
	static Ground::alphaColor mSwitchColor;

	/// <summary>
	/// �v���C���[�Ɗe�X�C�b�`�̋����̌v�Z
	/// </summary>
	/// <param name="_pPos">�v���C���[�̃|�W�V����</param>
	/// <param name="_sPos">�X�C�b�`�̃|�W�V����</param>
	void mSubtraction(Vector3 _pPos,Vector3 _sPos);

	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
	@param	��������GameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;

public: // �Q�b�^�[�A�Z�b�^�[
	// �v���C���[�ƃX�C�b�`�̋������擾
	static const float mGetDistance() { return mDistance; }

	// �X�C�b�`�̃J���[�^�O���擾
	static const Ground::alphaColor mGetSwitchTag() { return mSwitchColor; }

	//static const bool mGetSwitchFlag() { return mSwitchFlag; }
};

