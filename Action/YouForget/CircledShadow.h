/*
@brief �v���v���Z�b�T
*/
#pragma once


class CircledShadow : public ParticleEffectBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_Pos �e�G�t�F�N�g�̐����ꏊ
	@param	_Vel �e�G�t�F�N�g�̑��x
	@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
	@param	_SceneTag �V�[���̃^�O
	*/
	CircledShadow(const Vector3 _Pos, const Vector3 _Vel, const Tag& _ObjectTag, const SceneBase::SceneType _SceneTag, Player* _PlayerPtr);

	/*
	@fn	�f�X�g���N�^
	*/
	~CircledShadow() {};

	/*
	@fn		�e�G�t�F�N�g�̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

	// �v���C���[�̃|�C���^
	class Player* mPlayer;

};

