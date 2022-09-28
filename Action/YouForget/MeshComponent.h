/*
@file	MeshComponent.h
@brief	���b�V���f�[�^�̊Ǘ��ƕ`����s��
*/

/*
@brief	�v���v���Z�b�T
*/
#pragma once


class Shader;
class Mesh;

class MeshComponent : public Component
{
public:
	/*
	@fn		�R���X�g���N�^
	@param	_owner �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
	@param	_skelton �X�P���g���f�[�^��p���邩�B(�f�t�H��false)
	@sa		SkeletalMeshComponent.h
	*/
	MeshComponent(GameObject* _owner, bool _skelton = false);

	/*
	@fn		�f�X�g���N�^
	*/
	~MeshComponent();

	/*
	@fn		�`�揈��
	@param	_shader �g�p����V�F�[�_�[�N���X�̃|�C���^
	*/
	virtual void Draw(Shader* _shader);
protected:
	/*
	@fn		�e�N�X�`�����X�e�[�W���ƂɃZ�b�g
	@brief	�f�B�t���[�Y�}�b�v	stage00
			�@���}�b�v			stage01
			�X�y�L�����[�}�b�v	stage02
			���ȕ��˃}�b�v		stage03
	@param	_shader �g�p����V�F�[�_�[�N���X�̃|�C���^
	*/
	virtual void SetTextureToShader(class Shader* _shader);
	//���b�V���f�[�^�N���X�ւ̃|�C���^
	Mesh* mMesh;
	//�e�N�X�`���T�C�Y
	size_t mTextureIndex;
	//�`������邩�ǂ���
	bool mVisible;
	//�X�P���g���f�[�^��p���邩
	bool mSkeltonFlag;

public: //�Q�b�^�[�Z�b�^�[
	/*
	@fn		�`������邩�ǂ�����ݒ�
	@param	_visible true : �`�悷�� , false : �`�悵�Ȃ�
	*/
	void SetVisible(bool _visible) { mVisible = _visible; }

	/*
	@fn		�`������邩�ǂ������擾����
	@return	true : �`�悷�� , false : �`�悵�Ȃ�(bool�^)
	*/
	bool GetVisible() const { return mVisible; }

	/*
	@return �X�P���g���f�[�^��p���邩(bool�^)
	*/
	bool GetIsSkeltal()const { return mSkeltonFlag; }

	/*
	@return �ݒ肳�ꂽMesh�N���X�̃|�C���^(bool�^)
	*/
	virtual Mesh* GetMesh() { return mMesh; }

	/*
	@fn		���b�V���R���|�[�l���g���g��Mesh�̐ݒ�
	@param	_mesh �ݒ肷��Mesh�N���X�̃|�C���^
	*/
	virtual void SetMesh(Mesh* _mesh) { mMesh = _mesh; }

	/*
	@fn		���b�V���R���|�[�l���g���g��Texture�C���f�b�N�X�̐ݒ�
	@param _index �e�N�X�`���T�C�Y
	*/
	void SetTextureIndex(size_t _index) { mTextureIndex = _index; }
};