/*
@brief	プリプロセッサ
*/
#pragma once


class SandEffect :public ParticleEffectBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_pos 砂ぼこりの座標
	@param	_vel 砂ぼこりの速度
	@param	_objectTag アタッチしたゲームオブジェクトのタグ
	@param	_sceneTag シーンのタグ
	*/
	SandEffect(Vector3 _pos, Vector3 _vel, SceneBase::Scene _sceneTag, const Tag& _objectTag);

	/*
	@fn	デストラクタ
	*/
	~SandEffect() {};

	/*
	@fn		砂ぼこりのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
};

