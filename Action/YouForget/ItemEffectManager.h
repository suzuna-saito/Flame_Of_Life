/*
@brief プリプロセッサ
*/
#pragma once

/*
@brief 前方宣言
*/
class ItemEffect;
class Item;


class ItemEffectManager : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
	@param	_SceneTag シーンのタグ
	@param _ItemPtr アイテムのポインタ
	*/
	ItemEffectManager(const Tag& _ObjectTag, const SceneBase::SceneType _SceneTag, Item* _ItemPtr);

	/*
	@fn	デストラクタ
	*/
	~ItemEffectManager() {};

	/*
	@fn		エフェクトマネージャーのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	/*
	@brief アイテムエフェクトの方向
	*/
	enum class DirectionItemEffect :unsigned char
	{
		eLeftDeath,
		eBackDeath,
		eLeftBackDeath
	};


	/*
	@fn    速度を決める
	@param _Quantity 個数
	*/
	void DecideVelocity(const int _Quantity);

	//ゲームオブジェクトクラスのポインタ
	GameObject* mOwner;
	//パーティクルの状態
	ParticleEffectBase::ParticleState mState;
	//シーンのタグ
	SceneBase::SceneType mSceneTag;
	//アタッチしたゲームオブジェクトのタグ
	Tag				 mTag;
	//アイテムエフェクト
	ItemEffect* mItemEffect;
	//アイテムのポインタ
	Item* mItem;
	// ランダムの速度
	Vector3 mRandVel;

	//任意のタイミングでデスエフェクトを生成するためのカウント
	int				 mCreateItemEffectCount;

	//角度
	float			 mAngle;

	//アイテムエフェクトを生成するためのフラグ
	bool			 OneCreateItemFlag;

	bool farstFlag;
	

};

