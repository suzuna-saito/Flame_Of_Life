/*
@brief	�v���v���Z�b�T
*/
#pragma once

class VertexArray
{
public:

	/*
	@enum ���_���C�A�E�g
	*/
	enum Layout
	{
		//�ʒu&�@��&�e�N�X�`��UV ���������t�H�[�}�b�g
		PosNormTex,
		//�ʒu&�@��&"�X�L���p�̉e���{�[�����d�ݏ��" & �e�N�X�`��UV 
		PosNormSkinTex
	};

	/*
	@fn		�R���X�g���N�^
	@param	_verts ���_�o�b�t�@�̔z��̃|�C���^
	@param	_numVerts ���_��
	@param	_indices �C���f�b�N�X�o�b�t�@�̔z��̃|�C���^
	@param	_numIndices �C���f�b�N�X�̐�
	*/
	VertexArray(const float* _verts, unsigned int _numVerts,
		const unsigned int* _indices, unsigned int _numIndices);

	/*
	@fn		���_�z��R���X�g���N�^
	@param	_verts ���_�o�b�t�@�̔z��̃|�C���^
	@param	_numVerts ���_��
	@param	_layout ���_���C�A�E�g
	@param	_indices �C���f�b�N�X�o�b�t�@�̔z��̃|�C���^
	@param	_numIndices �C���f�b�N�X�̐�
	*/
	VertexArray(const void* _verts, unsigned int _numVerts, Layout _layout,
		const unsigned int* _indices, unsigned int _numIndices);

	/*
	@fn	�f�X�g���N�^
	*/
	~VertexArray();

	/*
	@fn ���_�z����A�N�e�B�u�ɂ���i�`��Ɏg�p�ł���悤�ɂ���j
	*/
	void SetActive();

	/*
	@fn		�C���f�b�N�X�o�b�t�@�ɂ���C���f�b�N�X�̐����擾����
	@return �C���f�b�N�X�̐�(unsigned int�^)
	*/
	unsigned int GetNumIndices() const { return mNumIndices; }

	/*
	@fn		���_�o�b�t�@�ɂ��钸�_�̐����擾����
	@return ���_�̐�(unsigned int�^)
	*/
	unsigned int GetNumVerts() const { return mNumVerts; }

private:

	//���_�o�b�t�@�ɂ��钸�_�̐�
	unsigned int mNumVerts;
	//�C���f�N�X�o�b�t�@�ɂ���C���f�b�N�X�̐�
	unsigned int mNumIndices;
	//���_�o�b�t�@��OpenGL ID
	unsigned int mVertexBuffer;
	//�C���f�b�N�X�o�b�t�@��OpenGL ID
	unsigned int mIndexBuffer;
	//���_�z��I�u�W�F�N�g��OpenGL ID
	unsigned int mVertexArray;
};

