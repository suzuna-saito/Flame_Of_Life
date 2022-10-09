/*
@brief �v���v���Z�b�T
*/
#pragma once

class GoalEffectManager : public GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
	@param	_SceneTag �V�[���̃^�O
	@param _ItemPtr Goal�̃|�C���^
	*/
	GoalEffectManager(const Tag& _ObjectTag, const SceneBase::SceneType _SceneTag, GoalObj* _PlayerPtr);

	/*
	@fn	�f�X�g���N�^
	*/
	~GoalEffectManager() {};

	/*
	@fn		�G�t�F�N�g�}�l�[�W���[�̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
	//�Q�[���I�u�W�F�N�g�N���X�̃|�C���^
	GameObject* mOwner;
	//�p�[�e�B�N���̏��
	ParticleEffectBase::ParticleState mState;
	//�V�[���̃^�O
	SceneBase::SceneType mSceneTag;
	//�A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
	Tag				 mTag;
	//�S�[���G�t�F�N�g
	GoalEffect* mGoalEffect;
	//�A�C�e���̃|�C���^
	GoalObj* mGoal;
	//�p�x
	float			 mAngle;
};

