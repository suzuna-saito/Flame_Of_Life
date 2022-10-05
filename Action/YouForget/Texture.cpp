#include "pch.h"

Texture::Texture()
	: mTextureID(0)
	, mWidth(0)
	, mHeight(0)
{
}

bool Texture::Load(const string& _fileName)
{
	// �`�����l�������i�[���郍�[�J���ϐ�
	int channels = 0;

	// �`�����l�������i�[���郍�[�J���ϐ�
	SDL_Surface* surf = IMG_Load(_fileName.c_str());
	if (!surf)
	{
		printf("�e�N�X�`���ǂݍ��݂Ɏ��s %s", _fileName.c_str());
		return false;	// false��Ԃ�
	}

	// SDL�T�[�t�F�X���e�N�X�`������쐬
	SDL_Texture* tex = nullptr;
	// SDL_CreateTextureFromSurface(�����_�����O�R���e�L�X�g�A�e�N�X�`���Ŏg���s�N�Z���f�[�^������SDL_Surface)
	tex = SDL_CreateTextureFromSurface(RENDERER->GetSDLRenderer(), surf);
	if (!tex)
	{
		printf("�T�[�t�F�X����e�N�X�`���̍쐬�Ɏ��s : %s", _fileName.c_str());
		return false;	// false��Ԃ�
	}

	// �摜�̕��A�����A�`�����l�������擾
	mWidth = surf->w;						// ��
	mHeight = surf->h;						// ����
	channels = surf->format->BytesPerPixel;	// �`�����l�����擾

	// OpenGL�Ƀe�N�X�`���o�^
	int format = GL_RGB;	// �A���t�@�Ȃ��t���J���[�i3�j
	int depth, pitch;
	depth = 24;				// �[�x�@24
	pitch = 3 * mWidth;		// 1�s�N�Z��������3byte * 1�s�̃s�N�Z����
	// �`�����l������4��������
	if (channels == 4)
	{
		format = GL_RGBA;	// �A���t�@�t���t���J���[�ɐݒ�i4�j
		depth = 32;			// �[�x�@32�ɐݒ�
		pitch = 4 * mWidth;	// 1�s�N�Z��������4byte * 1�s�̃s�N�Z���� 
	}

	// �e�N�X�`������1����
	glGenTextures(1, &mTextureID);
	// �w�肵�����O�̃e�N�X�`����L���ɂ���(2�����e�N�X�`��)
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	// �摜�f�[�^���֘A�t����(�^�[�Q�b�g�A���x���i0�̓x�[�X�摜���x���j�A�F�����̐��A�摜���A�摜�����A
	//						0�łȂ���΂Ȃ�Ȃ��A��f�f�[�^�̌`���A��f�f�[�^�̃f�[�^�^�A��������̉摜�f�[�^�ւ̃|�C���^)
	glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, surf->pixels);
	// RGB�T�[�t�F�C�X���������
	SDL_FreeSurface(surf);

	// �w�肳�ꂽ�e�N�X�`���I�u�W�F�N�g�̃~�b�v�}�b�v�𐶐�
	// (�e�N�X�`���I�u�W�F�N�g���o�C���h����Ώۂ��w��)
	glGenerateMipmap(GL_TEXTURE_2D);
	// �e�N�X�`�� �p�����[�^�[��ݒ�(2�����e�N�X�`�����g�p�A
	//							�k�����A�g�厞�̃t�B���^�����O���@�����ꂼ��w��A�⊮����t�B���^�[�i�o���`��ԁj��ݒ�)
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

void Texture::Unload()
{
	// ���O�t���e�N�X�`�����폜
	glDeleteTextures(1, &mTextureID);
}