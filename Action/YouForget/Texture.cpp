/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn	�R���X�g���N�^
*/
Texture::Texture()
	: mTextureID(0)
	, mWidth(0)
	, mHeight(0)
	, mLuminance(0)
{
}

/*
@fn	�f�X�g���N�^
*/
Texture::~Texture()
{
}

/*
@fn		�e�N�X�`���̃��[�h
@param	_fileName �e�N�X�`���̃t�@�C����
@return	true : ���� , false : ���s(bool�^)
*/
bool Texture::Load(const std::string& _fileName)
{
	int channels = 0;

	// SDL�T�[�t�F�X���e�N�X�`������쐬
	SDL_Texture* tex = nullptr;
	SDL_Surface* surf = IMG_Load(_fileName.c_str());
	if (!surf)
	{
		printf("�e�N�X�`���ǂݍ��݂Ɏ��s %s", _fileName.c_str());
		return false;
	}

	//�T�[�t�F�X����e�N�X�`�������
	tex = SDL_CreateTextureFromSurface(RENDERER->GetSDLRenderer(), surf);
	if (!tex)
	{
		printf("�T�[�t�F�X����e�N�X�`���̍쐬�Ɏ��s : %s", _fileName.c_str());
		return false;
	}

	// �摜�̕��A�������擾
	mWidth = surf->w;
	mHeight = surf->h;
	channels = surf->format->BytesPerPixel;

	// OpenGL�Ƀe�N�X�`���o�^
	int format = GL_RGB;
	int depth, pitch;
	depth = 24;
	pitch = 3 * mWidth; // 1�s�N�Z��������3byte * 1�s�̃s�N�Z����
	if (channels == 4)
	{
		format = GL_RGBA;
		depth = 32;
		pitch = 4 * mWidth;
	}

	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	// @@@
	glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, surf->pixels);

	SDL_FreeSurface(surf);

	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// �ٕ����t�B���^�����O���g���邩�ǂ���
	if (GLEW_EXT_texture_filter_anisotropic)
	{
		// �ő�ٕ̈����������l���擾����
		GLfloat largest;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest);
		// �ٕ����t�B���^�����O��L���ɂ���
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest);
	}

	return true;
}

/*
@fn	���[�h�����e�N�X�`���̉��
*/
void Texture::Unload()
{
	glDeleteTextures(1, &mTextureID);
}

/*
@fn		�T�[�t�F�C�X����쐬
@param	_surface �R�s�[�Ŏg����s�N�Z���̏W�܂�̍\����
*/
void Texture::CreateFromSurface(SDL_Surface* _surface)
{
	mWidth = _surface->w;
	mHeight = _surface->h;

	// Generate a GL texture
	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_BGRA,
		GL_UNSIGNED_BYTE, _surface->pixels);

	// Use linear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

/*
@fn		�����_�����O�p�̃e�N�X�`�����쐬
@param	_width �e�N�X�`���̉���
@param	_height �e�N�X�`���̏c��
@param	_format �s�N�Z���f�[�^�̃t�H�[�}�b�g
*/
void Texture::CreateForRendering(int _width, int _height, unsigned int _format)
{
	mWidth = _width;
	mHeight = _height;
	// �e�N�X�`��ID�̍쐬
	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	// �摜�̕��ƍ�����ݒ�i�����f�[�^�͎w�肵�Ȃ��j
	glTexImage2D(GL_TEXTURE_2D, 0, _format, mWidth, mHeight, 0, GL_RGB,
		GL_FLOAT, nullptr);

	// �����_�����O��̃e�N�X�`���ɂ͍ŋߖT�t�B���^�����O�݂̂��g��
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

/*
@fn	�e�N�X�`�����A�N�e�B�u�ɂ���
*/
void Texture::SetActive()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}