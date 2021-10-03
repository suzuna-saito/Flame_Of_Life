/*
@brief	�v���v���Z�b�T
*/
#pragma once


class UIBase : public GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_pos UI�̐����ꏊ(�X�N���[�����W)
	@param	_uiFileName �摜�ւ̃A�h���X
	@param	_objectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
	@param	_sceneTag �V�[���̃^�O
	@param	_scale �摜�̊g��T�C�Y
	*/
	UIBase(const Vector2& _pos, const std::string& _uiFileName, SceneBase::Scene _sceneTag, const Tag& _objectTag, const float& _scale = 10);

	/*
	@fn	�f�X�g���N�^
	*/
	~UIBase() {};

	/*
	@fn �h���N���X�̍X�V�֐����Ăэ��W�Ɉړ��ʂ𑫂�������
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

protected:

};
