/*
@brief プリプロセッサ
*/
#pragma once

/*
@brief 前方宣言
*/
class CircledShadow;

class CircledShadowManager : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
	@param	_SceneTag シーンのタグ
	@param _ItemPtr プレイヤーのポインタ
	*/
	CircledShadowManager(const Tag& _ObjectTag, const SceneBase::SceneType _SceneTag, Player* _PlayerPtr);

	/*
	@fn	デストラクタ
	*/
	~CircledShadowManager() {};

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
	//プレイヤーの影エフェクト
	CircledShadow* mCircledShadowEffect;
	//アイテムのポインタ
	Player* mPlayer;
	//角度
	float			 mAngle;
};

