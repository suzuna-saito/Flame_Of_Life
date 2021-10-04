/*
@brief	�v���v���Z�b�T
*/
#pragma once

/*
@brief	�C���N���[�h
*/

class Texture;
class SpriteComponent;

class Sprite : public GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_fileName �摜�t�@�C���̖��O
	*/
	Sprite(const std::string _fileName);

	/*
	@fn	�f�X�g���N�^
	*/
	~Sprite() {};

private:

	//�e�N�X�`���𐶐�
	Texture* mSpriteTexture;
	//SpriteComponent�𐶐�
	SpriteComponent* mSpriteComponent;

};

