/*
@brief	プリプロセッサ
*/
#pragma once


class SandEffect;
class SamplePlayer;

class EffectManager : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_owner ゲームオブジェクトクラスのポインタ
	@param	_objectTag アタッチしたゲームオブジェクトのタグ
	@param	_sceneTag シーンのタグ
	*/
	EffectManager(GameObject* _owner, const Tag& _objectTag, SceneBase::SceneType _sceneTag);

	/*
	@fn	デストラクタ
	*/
	~EffectManager() {};

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
	//エフェクトマネージャーの座標
	Vector3			 mPos;
	//シーンのタグ
	SceneBase::SceneType mSceneTag;
	//アタッチしたゲームオブジェクトのタグ
	Tag				 mTag;
	//砂ぼこりエフェクト
	SandEffect* mSandEffect;

	//任意のタイミングで砂ぼこりエフェクトを生成するためのカウント
	int				 mCreateSandEffectCount;
	//任意のタイミングでデスエフェクトを生成するためのカウント
	int				 mCreateDeathEffectCount;

	//角度
	float			 mAngle;
};

