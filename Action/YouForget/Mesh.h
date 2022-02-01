/*
@file	Mesh.h
@brief	���b�V���f�[�^
*/

/*
@brief	�v���v���Z�b�T
*/
#pragma once

class Renderer;
class VertexArray;
class Texture;

enum class TextureStage;

class Mesh
{
public:

	/*
	@fn	�R���X�g���N�^
	*/
	Mesh();

	/*
	@fn	�f�X�g���N�^
	*/
	~Mesh() {};

	/*
	@fn		���b�V���f�[�^�̓ǂݍ���
	@param	_fileName ���[�h���������b�V���̃t�@�C����
	@param	_renderer Renderer�N���X�̃|�C���^
	@return true : ���� , false : ���s(bool�^)
	*/
	bool Load(const std::string& _fileName, Renderer* _renderer);

	/*
	@fn	���[�h�������b�V���f�[�^�̉��
	*/
	void Unload();

private:

	//���̃��b�V���Ɏg���e�N�X�`���̃|�C���^�̉ϒ��R���e�i
	std::vector<Texture*> mTextures;
	//���̃��b�V���Ɏg�����_�f�[�^
	std::vector<Vector3> mVerts;
	//�N���X�̃|�C���^
	VertexArray* mVertexArray;

	//���̃��b�V���Ɏg���V�F�[�_�[�̖��O
	std::string mShaderName;
	//�I�u�W�F�N�g��Ԃł̋��E���̔��a
	float mRadius;
	//���ʔ��ː����̑傫��
	float mSpecPower;
	// ���Ȕ������x(HDR)
	float mLuminance;
	// �����x
	float mAlpha;

	//���b�V���̋�`�����蔻��
	AABB mBox;

	// �e�N�X�`���X�e�[�W�Ɋ��蓖�Ă�ꂽ�e�N�X�`��
	std::unordered_map<TextureStage, int> mStageDefTexture;

public://�Q�b�^�[�Z�b�^�[

	/*
	@return	VertexArray�^�̃|�C���^(class VertexArray)
	*/
	VertexArray* GetVertexArray() { return mVertexArray; }

	/*
	@param	_index �e�N�X�`���T�C�Y
	@return Texture�N���X�̃|�C���^(class Texture)
	*/
	Texture* GetTexture(size_t _index);

	/*
	@param	_stage �e�N�X�`���X�e�[�W
	@return �e�N�X�`����ID(int�^)
	*/
	int GetTextureID(TextureStage _stage);

	/*
	@return Texture�N���X�̃|�C���^(std::string�^)
	*/
	const std::string& GetShaderName() const { return mShaderName; }

	/*
	@return ���a(float�^)
	*/
	float GetRadius() const { return mRadius; }

	/*
	@return ���ʔ��ː���(float�^)
	*/
	float GetSpecPower() const { return mSpecPower; }

	/*
	@return ���Ȕ������x(float�^)
	*/
	float GetLuminace() const { return mLuminance; }

	/*
	@return �����x(float�^)
	*/
	float GetAlpha() const { return mAlpha; }

	/*
	@return ���b�V���̋�`�����蔻��(struct AABB)
	*/
	const AABB& GetBox() const { return mBox; }

	/*
	@return ���_�f�[�^(Vector3�^)
	*/
	std::vector<Vector3> GetVerts() { return mVerts; }
};