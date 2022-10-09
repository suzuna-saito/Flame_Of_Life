/*
@brief プリプロセッサ
*/
#pragma once

class GoalEffectManager : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
	@param	_SceneTag シーンのタグ
	@param _ItemPtr Goalのポインタ
	*/
	GoalEffectManager(const Tag& _ObjectTag, const SceneBase::SceneType _SceneTag, GoalObj* _PlayerPtr);

	/*
	@fn	デストラクタ
	*/
	~GoalEffectManager() {};

	/*
	@fn		エフェクトマネージャーのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
	//ゲームオブジェクトクラスのポインタ
	GameObject* mOwner;
	//パーティクルの状態
	ParticleEffectBase::ParticleState mState;
	//シーンのタグ
	SceneBase::SceneType mSceneTag;
	//アタッチしたゲームオブジェクトのタグ
	Tag				 mTag;
	//ゴールエフェクト
	GoalEffect* mGoalEffect;
	//アイテムのポインタ
	GoalObj* mGoal;
	//角度
	float			 mAngle;
};

