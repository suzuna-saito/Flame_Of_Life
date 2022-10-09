#pragma once

/*
* �摜�̓ǂݍ��݂��s���N���X
*/
class Texture
{
public:
	// �R���X�g���N�^
	Texture();
	// �f�X�g���N�^
	~Texture() {};

	/// <summary>
	/// �e�N�X�`���̃��[�h
	/// </summary>
	/// <param name="_fileName">�e�N�X�`���̃t�@�C����</param>
	/// <returns>true : ���� , false : ���s</returns>
	bool Load(const string& _fileName);

	// ���[�h�����e�N�X�`���̉��
	void Unload();

private:
	unsigned int mTextureID;	// ���̃e�N�X�`����ID
	int mWidth;					// �e�N�X�`���̉���
	int mHeight;				// �e�N�X�`���̏c��

public://�Q�b�^�[�Z�b�^�[
	// �e�N�X�`��ID���擾
	int GetTextureID()const { return mTextureID; }
	// �e�N�X�`���̉������擾
	int GetWidth() const { return mWidth; }
	// �e�N�X�`���̏c�����擾
	int GetHeight() const { return mHeight; }

};