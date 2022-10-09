#pragma once

/*
* UI�֘A�̊��N���X
*/
class UIBase : public GameObject
{
public:
	// �R���X�g���N�^
	UIBase();
	// �f�X�g���N�^
	virtual ~UIBase() {};

	//�@UI�̎�ށi�`�悵�������j
	enum UIType :unsigned char
	{
		eFullPicture,	// 1920�~1080�T�C�Y��UI
		ePuzzleBase,	// �p�Y���̊��
		ePuzzlePiece,	// �p�Y���̃s�[�X
		eText,			// �e�L�X�g
		eAButton,		// A�{�^��
	};

protected:
	class UIComponent* mUIComponent;	// UI�̕`��N���X

public:// �Q�b�^�[�A�Z�b�^�[
	// �摜��`�悷�邩���Ȃ����Z�b�g���� true:�`�悷��
	void SetThisVisible(bool _flag) { mUIComponent->SetVisible(_flag); }
};
