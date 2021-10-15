/*
@brief	プリプロセッサ
*/
#pragma once

class Candle :public GameObject
{
public:
	// コンストラクタ
	Candle(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	// デストラクタ
	~Candle() {};

	/*
	@fn		ろうそくのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;


private:
	//ゲームオブジェクトのメッシュポインタ変数
	MeshComponent* mMeshComponent;

	// 四角の地面の当たり判定を生成
	BoxCollider* mSelfBoxCollider;


	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数(足元判定用)
	@param	当たったGameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;


	// ろうそくの火がつくかどうか
	bool mFireFlag;
	// ろうそくの火を描画しているかどうか
	bool mDrawFireFlag;

	// 火がついたろうそくの本数
	static int mCandleCount;

public: // セッター、ゲッター
	// 火がついたろうそくの本数を返す
	int mGetCandleNum() { return mCandleCount; }


};

