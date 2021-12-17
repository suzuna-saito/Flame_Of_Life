/*
@brief	�v���v���Z�b�T
*/
#pragma once


class Texture
{
public:

	/*
	@fn	�R���X�g���N�^
	*/
	Texture();

	/*
	@fn	�f�X�g���N�^
	*/
	~Texture();

	/*
	@fn		�e�N�X�`���̃��[�h
	@param	_fileName �e�N�X�`���̃t�@�C����
	@return	true : ���� , false : ���s(bool�^)
	*/
	bool Load(const std::string& _fileName);

	/*
	@fn	���[�h�����e�N�X�`���̉��
	*/
	void Unload();

	/*
	@fn		�T�[�t�F�C�X����쐬
	@param	_surface �R�s�[�Ŏg����s�N�Z���̏W�܂�̍\����
	*/
	void CreateFromSurface(struct SDL_Surface* _surface);

	/*
	@fn		�����_�����O�p�̃e�N�X�`�����쐬
	@param	_width �e�N�X�`���̉���
	@param	_height �e�N�X�`���̏c��
	@param	_format �s�N�Z���f�[�^�̃t�H�[�}�b�g
	*/
	void CreateForRendering(int _width, int _height, unsigned int _format);

private:

	//�e�N�X�`��id
	unsigned int mTextureID;
	//�P�x
	float mLuminance;
	//�e�N�X�`���̉���
	int mWidth;
	//�e�N�X�`���̏c��
	int mHeight;

public://�Q�b�^�[�Z�b�^�[

	/*
	@return �e�N�X�`���̉���(int�^)
	*/
	int GetWidth() const { return mWidth; }

	/*
	@return �e�N�X�`���̏c��(int�^)
	*/
	int GetHeight() const { return mHeight; }

	/*
	@return �e�N�X�`��id(int�^)
	*/
	int GetTextureID() const { return mTextureID; }

	/*
	@fn	�e�N�X�`�����A�N�e�B�u�ɂ���
	*/
	void SetActive();

	/*
	@param _luminance �P�x
	*/
	void SetLuminace(float _luminance) { mLuminance = _luminance; }

};