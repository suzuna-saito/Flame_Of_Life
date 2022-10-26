#pragma once

/*
* �G�t�F�N�g�̊��N���X
*/
class ParticleEffectBase : public GameObject
{
public:
	// �p�[�e�B�N���̏��
	enum class ParticleState :unsigned char
	{
		eParticleActive,	// �A�N�e�B�u
		eParticleDisable,	// �����ɂ���
	};

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner">�A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^</param>
	/// <param name="_billFlag">�J�����̕������������ǂ��� true:����</param>
	/// <param name="_effectType">�G�t�F�N�g�̃^�C�v(�x�[�X��3D)</param>
	ParticleEffectBase(class GameObject* _owner, bool _billFlag = false, ParticleComponent::EffectType _effectType = ParticleComponent::EffectType::e3D);
	// �f�X�g���N�^
	virtual ~ParticleEffectBase() {};

protected:
	class ParticleComponent* mParticle;	// �p�[�e�B�N���̕`��N���X
	class GameObject* mOwner;			// �A�^�b�`�����I�u�W�F�N�g�̃|�C���^
	
	Vector3 mAngle;						// ��]�l
	float mFloatScale;					// �P�̃X�P�[���l�ifloat�j

public:	// �Q�b�^�[�A�Z�b�^�[
	// �摜��`�悷�邩���Ȃ����Z�b�g���� true:�`�悷��
	void SetThisVisible(bool _flag) { mParticle->SetVisible(_flag); }
};