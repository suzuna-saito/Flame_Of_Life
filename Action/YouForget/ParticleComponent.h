#pragma once

/*
* �G�t�F�N�g��3D��ԏ�ɕ`�悷��N���X
*/
class ParticleComponent : public Component
{
public:
	// �G�t�F�N�g��2�c��3�c��
	enum class EffectType :unsigned char
	{
		e2D,		// 2D�G�t�F�N�g
		e3D,		// 3D�G�t�F�N�g
	};

	// �p�[�e�B�N���ɑ΂���u�����h�̃^�C�v
	enum class ParticleBlendType :unsigned char
	{
		eAlphaBlend,// �A���t�@�u�����h
		eAddBlend,	// ���Z����
		eMultBlend	// ��Z����
	};

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner">�A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^</param>
	/// <param name="_billFlag">�J�����̕������������ǂ��� true:����</param>
	/// <param name="_effectType">�G�t�F�N�g�̃^�C�v</param>
	/// <param name="_updateOrder">�R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j</param>
	ParticleComponent(GameObject* _owner, bool _billFlag , EffectType _effectType,int _updateOrder = 100);
	// �f�X�g���N�^
	~ParticleComponent();

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="_shadere">�g�p����V�F�[�_�[�N���X�̃|�C���^</param>
	void Draw(class Shader* _shadere);

private:
	/// <summary>
	/// �r���{�[�h�s����擾(Matrix4)
	/// </summary>
	/// <returns>�r���{�[�h�s��</returns>
	Matrix4 GetBillboardMatrix();

	class Texture* mTexture;		// �e�N�X�`��

	EffectType mEffectType;			// �G�t�F�N�g��2�c��3�c��(�x�[�X��3D)
	ParticleBlendType mBlendType;	// �u�����h�^�C�v

	Matrix4 mStaticBillboardMat;	// �r���{�[�h�s��

	Vector3 mAngle;					// �G�t�F�N�g�̊p�x

	int mDrawOrder;			// �`�揇(���������Ȃ����̂���`�悳���)
	int mTextureWidth;		// �e�N�X�`���̉���
	int mTextureHeight;		// �e�N�X�`���̏c��

	bool mVisible;			// �`����s���� true:�s��
	bool mBillboardFlag;	// �J�����̕������������ǂ��� true:����

public: // �Q�b�^�[�Z�b�^�[
	// �G�t�F�N�g�̃^�C�v���擾
	const EffectType GetEffectType() const { return mEffectType; }
	// �u�����h�^�C�v���擾
	const ParticleBlendType GetBlendType() const { return mBlendType; }

	// �`�揇���擾
	const int GetDrawOrder() const { return mDrawOrder; }
	// �`������邩�ǂ������擾 true:�`�悷��
	const bool GetVisible() const { return mVisible; }

	/// <summary>
	/// �u�����h�^�C�v��ݒ�
	/// </summary>
	/// <param name="_blendType">�u�����h</param>
	void SetBlendMode(ParticleBlendType _blendType) { mBlendType = _blendType; }

	/// <summary>
	/// �G�t�F�N�g�̊p�x��ݒ�
	/// </summary>
	/// <param name="_angle">�G�t�F�N�g�̊p�x</param>
	void SetAngle(const Vector3& _angle) { mAngle = _angle; }

	/// <summary>
	/// �e�N�X�`�����Z�b�g���c���̒������v�Z����
	/// </summary>
	/// <param name="_texture">�g�p����e�N�X�`���̃|�C���^</param>
	void SetTexture(class Texture* _texture);

	/// <summary>
	/// �`������邩�ǂ�����ݒ�
	/// </summary>
	/// <param name="_visible">�`��t���O true: �`�悷��</param>
	void SetVisible(bool _visible) { mVisible = _visible; }
};