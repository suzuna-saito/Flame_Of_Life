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
CircledShadowManager::CircledShadowManager(const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _mPlayer)
	:GameObject(_SceneTag, _ObjectTag)
{
	mState = ParticleState::PARTICLE_ACTIVE;
	mSceneTag = _SceneTag;
	mTag = _ObjectTag;

	mAngle = 0.0f;

	mPlayer = _mPlayer;

	mPosition = mPlayer->GetPosition();
	mPosition.z = mPlayer->GetPosition().z ;

	mCircledShadowEffect = new CircledShadow(mPosition, Vector3::Zero, mTag, mSceneTag, mPlayer);
}

/*
@fn		�G�t�F�N�g�}�l�[�W���[�̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void CircledShadowManager::UpdateGameObject(float _deltaTime)
{

}
