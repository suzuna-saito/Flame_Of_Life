#pragma once

/*
* UI�N���X���Ǘ����A�X�N���[����ɕ`�悷��N���X
*/
class UIComponent : public Component
{
public:
	// ��O�ɕ`�悷�邩�A���ɕ`�悷�邩
	enum class UIDrawType :unsigned char
	{
		eNear,	// ��O���ɕ`��
		eFar,	// �����ɕ`��
	};

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner">�A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^</param>
	/// <param name="_drawOrder">�R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j</param>
	/// <param name="_uiType">UI����O�ɕ`�悷�邩���ɕ`�悷�邩���ʂ���^�O �i�x�[�X�͎�O���ɕ`��j</param>
	UIComponent(class GameObject* _owner, const int _drawOrder, const UIDrawType _uiDrawType = UIDrawType::eNear);
	// �f�X�g���N�^
	~UIComponent();

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="_shader">�g�p����V�F�[�_�[�N���X�̃|�C���^</param>
	void Draw(class Shader* _shader);

private:
	class Texture* mTexture;	// �e�N�X�`��
	
	UIDrawType mUIDrawType;		// UI�̃^�C�v

	int mDrawOrder;				// �`�悳��鏇�ԁi���l�����Ȃ��قǑ����X�V�����j

	int mTextureWidth;			// �e�N�X�`���̉���
	int mTextureHeight;			// �e�N�X�`���̏c��

	bool mVisible;				// �`����s����

public://�Q�b�^�[�Z�b�^�[
	/// <summary>
	/// UI�̃^�C�v���擾
	/// </summary>
	/// <returns></returns>
	UIDrawType GetUIDrawType()const { return mUIDrawType; }

	/// <summary>
	/// �`��ԍ����擾
	/// </summary>
	/// <returns>�`�悳��鏇�ԁi���l�����Ȃ��قǑ����X�V�����j</returns>
	int GetDrawOrder()const { return mDrawOrder; }

	/// <summary>
	/// �`������邩�ǂ������擾����
	/// </summary>
	/// <returns>true : �`�悷��</returns>
	bool GetVisible() const { return mVisible; }

	/// <summary>
	/// �e�N�X�`�����Z�b�g���c���̒������v�Z����
	/// </summary>
	/// <param name="_texture">�g�p����e�N�X�`���̃|�C���^</param>
	void SetTexture(class Texture* _texture);

	/// <summary>
	/// �`������邩�ǂ�����ݒ�
	/// </summary>
	/// <param name="_visible">true : �`�悷��</param>
	void SetVisible(bool _visible) { mVisible = _visible; }
};