#pragma once

/*
* �X�g�[���[��i�߂邽�߂̃{�^��UI�̍X�V�A�`�悷��N���X
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
	const float mMaxScale;	// �X�P�[���̍ő�l
	const float mMinScale;	// �X�P�[���̍ŏ��l
	float mAddScale;		// �X�P�[���̑����l
};