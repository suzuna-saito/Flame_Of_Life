#pragma once

/*
* 1920�~1080�T�C�Y�̉摜��`�悷��N���X
*/
class FullPicture : public UIBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_fileName">�摜�t�@�C���̖��O</param>
	/// <param name="_uiDrawType">�摜����Ԃɕ`�悷�邩���ɕ`�悷�邩�i�x�[�X�͎�O���j</param>
	FullPicture(const string _fileName, const UIComponent::UIDrawType _uiDrawType = UIComponent::UIDrawType::eNear);
	// �f�X�g���N�^
	~FullPicture() {};
};