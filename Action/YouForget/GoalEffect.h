/*
@brief �v���v���Z�b�T
*/
#pragma once


class GoalEffect : public ParticleEffectBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_Pos �S�[���G�t�F�N�g�̐����ꏊ
	@param	_Vel �S�[���G�t�F�N�g�̑��x
	@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
	@param	_SceneTag �V�[���̃^�O
	*/
	GoalEffect(const Vector3 _Pos, const Vector3 _Vel, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, GoalObj* _PlayerPtr);

	/*
	@fn	�f�X�g���N�^
	*/
	~GoalEffect() {};

	/*
	@fn		�S�[���G�t�F�N�g�̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

	// �S�[���̃|�C���^
	class GoalObj* mGoal;

};

