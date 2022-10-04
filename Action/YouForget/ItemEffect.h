#pragma once

/*
@brief プリプロセッサ
*/
#pragma once

/*
@brief 前方宣言
*/
class Item;

class ItemEffect : public ParticleEffectBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_Pos アイテムエフェクトの生成場所
	@param	_Vel アイテムエフェクトの速度
	@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
	@param	_SceneTag シーンのタグ
	*/
	ItemEffect(const Vector3 _Pos, const Vector3 _Vel, const Tag& _ObjectTag, const SceneBase::SceneType _SceneTag, Item* _ItemPtr);

	/*
	@fn	デストラクタ
	*/
	~ItemEffect() {};

	/*
	@fn		アイテムエフェクトのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

	bool mItemVisible;
	
	//アイテムのポインタ
	Item* mItem;

public:
	void SetItemEffectPos(Vector3 _pos) { mPosition = _pos; }

	bool GetItemVisible() { return mItemVisible; }
};

