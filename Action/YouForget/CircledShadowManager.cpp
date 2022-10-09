/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
@param	_SceneTag シーンのタグ
@param _ItemPtr アイテムのポインタ
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
@fn		エフェクトマネージャーのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void CircledShadowManager::UpdateGameObject(float _deltaTime)
{

}
