/*
@brief プリプロセッサ
*/
#pragma once


class GoalEffect : public ParticleEffectBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_Pos ゴールエフェクトの生成場所
	@param	_Vel ゴールエフェクトの速度
	@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
	@param	_SceneTag シーンのタグ
	*/
	GoalEffect(const Vector3 _Pos, const Vector3 _Vel, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, GoalObj* _PlayerPtr);

	/*
	@fn	デストラクタ
	*/
	~GoalEffect() {};

	/*
	@fn		ゴールエフェクトのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

	// ゴールのポインタ
	class GoalObj* mGoal;

};

