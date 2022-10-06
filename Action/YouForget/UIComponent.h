/*
@file  SpriteComponent.h
@brief �摜�f�[�^�N���X���Ǘ����A�X�N���[����ɕ`�悷��N���X
*/

/*
@brief �v���v���Z�b�T
*/
#pragma once

/*
@brief �O���錾
*/
class GameObject;
class Shader;
class Texture;
class Vector3;

class UIComponent : public Component
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_owner �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
	@param	_scale UI�X�P�[��
	@param	_drawOrder �`��̏��ԁi���l���������قǑ����`�悳���j
	*/
	UIComponent(GameObject* _owner, const Vector3 _pos,const Vector3 _scale, int _drawOrder = 100);

	/*
	@fn		�f�X�g���N�^
	*/
	~UIComponent();

	/*
	@fn		�`�揈��
	@param _shader �g�p����V�F�[�_�[�N���X�̃|�C���^
	*/
	virtual void Draw(Shader* _shader, const Vector3& _Pos, const Vector3 _scale);

protected:

	//�N���X�̃|�C���^
	Texture* mTexture;
	//�`�悳��鏇�ԁi���l�����Ȃ��قǑ����X�V�����j
	int mDrawOrder;
	//�e�N�X�`���̉���
	int mTextureWidth;
	//�e�N�X�`���̏c��
	int mTextureHeight;
	//�`����s����
	bool mVisible;
	//UI��ID�A�J�E���g�p
	static int mUIid;
	//����UI��ID
	int mMyUIid;
	// UI�̃X�P�[��
	Vector3 mScale;
	// �|�W�V����
	Vector3 mPos;

public://�Q�b�^�[�Z�b�^�[

	/*
	@return �e�N�X�`���̉���(int�^)
	*/
	int GetTexWidth() const { return mTextureWidth; }

	/*
	@return �e�N�X�`���̏c��(int�^)
	*/
	int GetTexHeight() const { return mTextureHeight; }

	/*
	@return �`�揇(int�^)
	*/
	int GetDrawOrder() { return mDrawOrder; }

	/*
	@fn		�`������邩�ǂ������擾����
	@return	true : �`�悷�� , false : �`�悵�Ȃ�(bool�^)
	*/
	bool GetVisible() const { return mVisible; }

	/*
	@return	UI��id(int�^)
	*/
	int GetUIid() { return mMyUIid; }

	/*
	@fn		�e�N�X�`�����Z�b�g���c���̒������v�Z����
	@param	_texture �g�p����e�N�X�`���̃|�C���^
	*/
	virtual void SetTexture(Texture* _texture);

	/*
	@fn		�`������邩�ǂ�����ݒ�
	@param	_visible true : �`�悷�� , false : �`�悵�Ȃ�
	*/
	void SetVisible(bool _visible) { mVisible = _visible; }

	Vector3 GetScale()const { return mScale; }
	void SetScale(const Vector3 _scale) { mScale = _scale; }
	Vector3 GetPos()const { return mPos; }
};

