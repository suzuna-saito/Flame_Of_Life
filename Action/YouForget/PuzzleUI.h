#pragma once

/*
* �p�Y���̊�ՁA�s�[�X��`�悷��N���X
*/
class PuzzleUI : public UIBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_fileName">�摜�t�@�C���̖��O</param>
	PuzzleUI(const string _fileName,const UIType _type);
	// �f�X�g���N�^
	~PuzzleUI() {};

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="_deltaTime">�Ō�̃t���[������������̂ɗv��������</param>
	void UpdateGameObject(float _deltaTime)override;

private:
	UIType mType;	// �s�[�X����Ղ����ʗp
};