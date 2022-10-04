/*
@brief プリプロセッサ
*/
#pragma once


class CircledShadow : public ParticleEffectBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_Pos 影エフェクトの生成場所
	@param	_Vel 影エフェクトの速度
	@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
	@param	_SceneTag シーンのタグ
	*/
	CircledShadow(const Vector3 _Pos, const Vector3 _Vel, const Tag& _ObjectTag, const SceneBase::SceneType _SceneTag, Player* _PlayerPtr);

	/*
	@fn	デストラクタ
	*/
	~CircledShadow() {};

	/*
	@fn		影エフェクトのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

	// プレイヤーのポインタ
	class Player* mPlayer;

};

