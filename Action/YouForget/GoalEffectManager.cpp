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
@fn		エフェクトマネージャーのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void GoalEffectManager::UpdateGameObject(float _deltaTime)
{

}
