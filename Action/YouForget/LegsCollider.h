/*
@brief	プリプロセッサ
*/
#pragma once

class LegsCollider :public GameObject
{
public:

	/*
	@fn		コンストラクタ
	*/
	LegsCollider(Player* _owner, const Tag& _objectTag, const SceneBase::SceneType _sceneTag);

	/*
	@fn	デストラクタ
	*/
	~LegsCollider() {};

	/*
	@fn	更新
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	//プレイヤーの足元当たり判定を生成
	BoxCollider* mLegsBoxCollider;

	Player* mOwner;
	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数(足元判定用)
	@param	当たったGameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;


	// 設置判定
	bool mIsGround;

public://ゲッターセッター

	/*
	@return	地面との当たり判定
	*/
	const bool GetIsGround() const { return mIsGround; }

	void SetIsGround(bool _groundFlag) { mIsGround = _groundFlag; }
};


