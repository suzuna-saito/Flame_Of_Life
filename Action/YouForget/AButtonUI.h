#pragma once

/*
* �X�g�[���[��i�߂邽�߂̃{�^��UI�̍X�V
*/
class AButtonUI :public UIBase
{
public:
	// �R���X�g���N�^
	AButtonUI();
	// �f�X�g���N�^
	~AButtonUI() {};

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="_deltaTime">�Ō�̃t���[������������̂ɗv��������</param>
	void UpdateGameObject(float _deltaTime)override;

private:
	float mAddScale;	// �X�P�[���̑����l
};