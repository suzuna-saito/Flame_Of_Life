#pragma once

/*
* ��ʂ̑傫���ɂ������摜��`�悷��N���X
*/
class FullPicture : public UIBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_fileName">�摜�t�@�C���̖��O</param>
	FullPicture(const string _fileName);
	// �f�X�g���N�^
	~FullPicture() {};

private:
	class Texture* mFullPictureTexture;	//�e�N�X�`���𐶐�
	class UIComponent* mUIComponent;	//SpriteComponent�𐶐�

public:
	void SetThisVisible(bool _flag) { mUIComponent->SetVisible(_flag); }

	bool GetThisVisible() { return mUIComponent->GetVisible(); }
};

