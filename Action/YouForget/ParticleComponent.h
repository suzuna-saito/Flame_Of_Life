#pragma once

/*
* �G�t�F�N�g��3D��ԏ�ɕ`�悷��N���X
*/
class ParticleComponent : public Component
{
public:
	// �p�[�e�B�N���ɑ΂���u�����h�̃^�C�v
	typedef enum class ParticleBlendType :unsigned char
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
	/// <param name="_updateOrder">�R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j</param>
	ParticleComponent(GameObject* _owner, bool _billFlag ,int _updateOrder = 100);
	// �f�X�g���N�^
	~ParticleComponent();

	/*
	@fn		�t���[�����̏���
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	virtual void Update(float _deltaTime) override {};

	/*
	@fn		�`�揈��
	@param	_shader �g�p����V�F�[�_�[�N���X�̃|�C���^
	*/
	void Draw(class Shader* _shader);

	// �J���������ł̃\�[�g�p
	bool operator < (const ParticleComponent& _rhs) const;
	bool operator > (const ParticleComponent& _rhs) const;
private:
	// �p�x
	Vector3 mAngle;
	//�e�N�X�`��ID
	int mTextureID;
	//�u�����h�^�C�v
	ParticleBlendType mBlendType;
	//�`����s����
	bool mVisible;
	// �r���{�[�h�s��
	Matrix4 mStaticBillboardMat;
	// �J�����̃��[���h���W
	Vector3 mStaticCameraWorldPos;
	//�`�揇(���������Ȃ����̂���`�悳���)
	int mDrawOrder;
	//���]���s����
	bool mReverce;
	// �J�����̕������������ǂ��� _true ����,_false �����Ȃ�
	bool mBillboardFlag;
public: //�Q�b�^�[�Z�b�^�[
	/*
	@return �e�N�X�`��ID(int�^)
	*/
	int GetTextureID() { return mTextureID; }

	/*
	@return �u�����h�^�C�v(enum�^ PARTICLE_ENUM)
	*/
	ParticleBlendType GetBlendType() { return mBlendType; }

	/*
	@fn		�`������邩�ǂ������擾����
	@return	true : �`�悷�� , false : �`�悵�Ȃ�(bool�^)
	*/
	bool GetVisible() const { return mVisible; }

	/*
	@return �`�揇(int�^)
	*/
	int GetDrawOrder() { return mDrawOrder; }

	/*
	@param _texId �e�N�X�`��ID
	*/
	void SetTextureID(int _texId) { mTextureID = _texId; }

	/*
	@param mAngle �p�x�i�����j
	*/
	void SetAngle(const Vector3& _angle) { mAngle = _angle; }

	/*
	@param _mat �r���{�[�h�s��
	*/
	void SetBillboardMat(const Matrix4& _mat) { mStaticBillboardMat = _mat; }

	/*
	@param _brendType �J�����̃��[���h���W
	*/
	void SetBlendMode(ParticleBlendType _blendType) { mBlendType = _blendType; }

	/*
	@fn		�`������邩�ǂ�����ݒ�
	@param	_visible true : �`�悷�� , false : �`�悵�Ȃ�
	*/
	void SetVisible(bool _visible) { mVisible = _visible; }

	/*
	@param _drawOrder �`�揇
	*/
	void SetDrawOrder(int _drawOrder) { mDrawOrder = _drawOrder; }

	/*
	@param _flag ���]���s����
	*/
	void SetReverce(bool _flag) { mReverce = _flag; }
};

/*
@return �r���{�[�h�s��(Matrix4)
*/
Matrix4 GetBillboardMatrix();