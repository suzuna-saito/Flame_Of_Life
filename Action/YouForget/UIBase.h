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
	~UIBase() {};

protected:
	UIComponent* mUiComponent;	// UI�̕`��N���X

public:// �Q�b�^�[�A�Z�b�^�[
	// �摜��`�悷�邩���Ȃ����Z�b�g���� true:�`�悷��
	void SetThisVisible(bool _flag) { mUiComponent->SetVisible(_flag); }
};
