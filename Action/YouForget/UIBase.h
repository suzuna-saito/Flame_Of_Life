#pragma once

/*
* UI�֘A�̊��N���X
*/
class UIBase : public GameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_pos">UI�̐����ꏊ�i�X�N���[�����W�j</param>
	/// <param name="_uiFileName">�摜�ւ̃A�h���X</param>
	/// <param name="_sceneTag">�����������̃V�[��</param>
	/// <param name="_objectTag">�A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O</param>
	/// <param name="_scale">�摜�̊g��T�C�Y</param>
	UIBase(const Vector2& _pos, const string& _uiFileName, SceneBase::SceneType _sceneTypeTag, const Tag& _objectTag, const float& _scale = 1);
	// �f�X�g���N�^
	~UIBase() {};

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="_deltaTime">�Ō�̃t���[������������̂ɗv��������</param>
	void UpdateGameObject(float _deltaTime)override;

protected:
	//UI�̕`��N���X
	UIComponent* mUI;
};
