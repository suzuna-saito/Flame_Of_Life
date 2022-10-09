/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
@param	_SceneTag �V�[���̃^�O
@param _ItemPtr �A�C�e���̃|�C���^
*/
GoalEffectManager::GoalEffectManager(const Tag& _ObjectTag, const SceneBase::SceneType _SceneTag, GoalObj* _mPlayer)
	:GameObject(_SceneTag, _ObjectTag)
{
	mState = ParticleEffectBase::ParticleState::eParticleActive;
	mSceneTag = _SceneTag;
	mTag = _ObjectTag;

	mGoal = _mPlayer;

	mPosition = mGoal->GetPosition();

	mGoalEffect = new GoalEffect(mPosition, Vector3::Zero, mTag, mSceneTag, mGoal);
}

/*
@fn		�G�t�F�N�g�}�l�[�W���[�̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void GoalEffectManager::UpdateGameObject(float _deltaTime)
{

}
