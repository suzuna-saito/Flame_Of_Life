/*
@brief �v���v���Z�b�T
*/
#pragma once

class ButtonUI :public UIBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_Pos �v���C���[�̗̑�UI�̐����ꏊ(�X�N���[�����W)
	@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
	@param	_SceneTag �V�[���̃^�O
	@param _playerPtr �v���C���[�̃|�C���^
	*/
	ButtonUI(const Vector2& _Pos, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag);

	/*
	@fn	�f�X�g���N�^
	*/
	~ButtonUI() {};

	/*
	@fn		�v���C���[�̗̑�UI�̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
};