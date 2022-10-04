#pragma once

/*
@brief プリプロセッサ
*/
#pragma once

class FallEffect : public ParticleEffectBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_Pos デスエフェクトの生成場所
	@param	_Vel クリアエフェクトの速度
	@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
	@param	_SceneTag シーンのタグ
	*/
	FallEffect(const Vector3 _Pos, const Vector3 _Vel, const Tag& _ObjectTag, const SceneBase::SceneType _SceneTag);

	/*
	@fn	デストラクタ
	*/
	~FallEffect() {};

	/*
	@fn		デスエフェクトのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
	//アルファ値の削減値
	const float MAlphaReductionVal;
	//スケールの追加値
	const float MScaleAddVal;
};

