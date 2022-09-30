/*
@file ParticleComponent.h
@brief �摜���Ǘ��������3D��ԏ�ɕ`�悷��N���X�B
*/

/*
@brief	�v���v���Z�b�T
*/
#pragma once


class ParticleComponent : public Component
{
public:

	//�p�[�e�B�N���ɑ΂���u�����h�̎��
	typedef enum class PARTICLE_BLEND_ENUM :unsigned char
	{
		PARTICLE_BLEND_ENUM_ALPHA,
		PARTICLE_BLEND_ENUM_ADD,
		PARTICLE_BLEND_ENUM_MULT
	}PARTICLE_ENUM;

	/*
	@fn		�R���X�g���N�^
	@param	_owner �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
	@param	_offset �e�I�u�W�F�N�g�N���X�Ɖ摜��`�悷��ʒu�̍�
	@param	_scale �摜�̕`��T�C�Y
	@param	_updateOrder �R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j
	*/
	ParticleComponent(GameObject* _owner, bool _billFlag = false ,const Vector3& _offset = Vector3(1, 1, 1), float _scale = 1.0f, int _updateOrder = 100);

	/*
	@fn	�f�X�g���N�^
	*/
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
	//�e�I�u�W�F�N�g�N���X�Ɖ摜��`�悷��ʒu�̍�
	Vector3 mOffset;
	//�摜�ɏ�Z����F
	Vector3 mColor;
	//�T�C�Y
	float mScale;
	//�����x
	float mAlpha;
	// �p�x
	float mAngle;
	// ��]
	float mRot;
	//�e�N�X�`��ID
	int mTextureID;
	//�u�����h�^�C�v
	PARTICLE_ENUM mBlendType;
	//�`����s����
	bool mVisible;
	// �r���{�[�h�s��
	static Matrix4 mStaticBillboardMat;
	// �J�����̃��[���h���W
	static Vector3 mStaticCameraWorldPos;
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
	PARTICLE_ENUM GetBlendType() { return mBlendType; }

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
	@param _color �摜�ɏ�Z����F
	*/
	void SetColor(const Vector3& _color) { mColor = _color; }

	/*
	@param _alfa �����x0~1
	*/
	void SetAlpha(float _alpha) { mAlpha = _alpha; }

	/*
	@param mAngle �p�x�i�����j
	*/
	void SetAngle(float _angle) { mAngle = _angle; }

	/*
	@param _alfa �p�x�i�����j
	*/
	void SetRot(float _rot) { mRot = _rot; }

	/*
	@param _scale �X�P�[��
	*/
	void SetScale(float _scale) { mScale = _scale; }

	/*
	@param _mat �r���{�[�h�s��
	*/
	void SetBillboardMat(const Matrix4& _mat) { mStaticBillboardMat = _mat; }

	/*
	@param _brendType �J�����̃��[���h���W
	*/
	void SetBlendMode(PARTICLE_ENUM _blendType) { mBlendType = _blendType; }

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
	@param _offset �e�I�u�W�F�N�g�̍��W�ƕ`��ʒu�̍�
	*/
	void SetOffSet(Vector3 _offset) { mOffset = _offset; };

	/*
	@param _flag ���]���s����
	*/
	void SetReverce(bool _flag) { mReverce = _flag; }
};

/*
@return �r���{�[�h�s��(Matrix4)
*/
Matrix4 GetBillboardMatrix();