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
CircledShadowManager::CircledShadowManager(const Tag& _ObjectTag, const SceneBase::SceneType _SceneTag, Player* _mPlayer)
	:GameObject(_SceneTag, _ObjectTag)
{
	mState = ParticleEffectBase::ParticleState::eParticleActive;
	mSceneTag = _SceneTag;
	mTag = _ObjectTag;

	mAngle = 0.0f;

	mPlayer = _mPlayer;

	mPosition = mPlayer->GetPosition();
	mPosition.z = mPlayer->GetPosition().z ;

	mCircledShadowEffect = new CircledShadow(mPlayer);
}

/*
@fn		�G�t�F�N�g�}�l�[�W���[�̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void CircledShadowManager::UpdateGameObject(float _deltaTime)
{

}
