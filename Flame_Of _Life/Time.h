#pragma once

class Time :public UIBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_pos �v���C���[�̗̑�UI�̐����ꏊ(�X�N���[�����W)
	@param	_objectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
	@param	_sceneTag �V�[���̃^�O
	*/
	Time(const Vector2& _pos, const Tag& _objectTag, SceneBase::Scene _sceneTag);

	/*
	@fn	�f�X�g���N�^
	*/
	~Time() {};

	/*
	@fn		�v���C���[�̗̑�UI�̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

};