/*
@file	SkeletalMeshComponent.h
@brief	�X�P���g���f�[�^�̕`��ƃA�j���[�V����
*/

/*
@brief	�v���v���Z�b�T
*/
#pragma once


class SkeletalMeshComponent : public MeshComponent
{
public:
	/*
	@fn		�R���X�g���N�^
	@param	_owner �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
	*/
	SkeletalMeshComponent(class GameObject* _owner);

	/*
	@fn		�t���[�����̏���
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void Update(float _deltaTime) override;

	/*
	@fn		�`�揈��
	@param	_shader �g�p����V�F�[�_�[�N���X�̃|�C���^
	*/
	void Draw(class Shader* _shader) override;

	/*
	@fn		�A�j���[�V�����̍Đ�
	@param	_anim �A�j���[�V�����f�[�^�N���X
	@param	_playRate �A�j���[�V�����̍Đ����x
	@return	�A�j���[�V�����̎c�莞��(float�^)
	*/
	float PlayAnimation(const class Animation* _anim, float _playRate = 1.0f);
protected:
	/*
	@fn �s��p���b�g�̌v�Z
	*/
	void ComputeMatrixPalette();

	// �s��p���b�g
	MatrixPalette mPalette;
	// �X�P���g���f�[�^
	const class Skeleton* mSkeleton;
	// �A�j���[�V�����f�[�^
	const class Animation* mAnimation;
	// �A�j���[�V�����̍Đ����x
	float mAnimPlayRate;
	// �A�j���[�V��������
	float mAnimTime;
	//�X�P���g���f�[�^�ɏ�Z����F
	Vector3 mColor;
	
private:
	//�e�N�X�`���T�C�Y
	size_t mTextureIndex;

public://�Q�b�^�[�Z�b�^�[
	/*
	@param _skeleton �X�P���g���f�[�^
	*/
	void SetSkeleton(const class Skeleton* _skeleton) { mSkeleton = _skeleton; }
	/*
	@param _color �X�P���g���f�[�^�ɏ�Z����F
	*/
	void SetColor(const Vector3& _color) { mColor = _color; }
};
