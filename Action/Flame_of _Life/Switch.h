#pragma once

// 球体のオブジェクト
class Switch :public GameObject
{
public:

	// コンストラクタ
	Switch(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag, const Ground::alphaColor& _tag);

	/*
	@fn	デストラクタ
	*/
	~Switch() {};

	// 更新
	void UpdateGameObject(float _deltaTime)override;

	// スイッチを押しているかのフラグ
	static bool mSwitchFlag;
private:

	//ゲームオブジェクトのメッシュポインタ変数
	MeshComponent* mMeshComponent;

	// 四角の地面の当たり判定を生成
	BoxCollider* mSelfBoxCollider;

	// プレイヤーとスイッチの距離
	static float mDistance;

	// スイッチと連携している床の色
	static Ground::alphaColor mSwitchColor;

	/// <summary>
	/// プレイヤーと各スイッチの距離の計算
	/// </summary>
	/// <param name="_pPos">プレイヤーのポジション</param>
	/// <param name="_sPos">スイッチのポジション</param>
	void mSubtraction(Vector3 _pPos,Vector3 _sPos);

	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数
	@param	当たったGameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;

public: // ゲッター、セッター
	// プレイヤーとスイッチの距離を取得
	static const float mGetDistance() { return mDistance; }

	// スイッチのカラータグを取得
	static const Ground::alphaColor mGetSwitchTag() { return mSwitchColor; }

	//static const bool mGetSwitchFlag() { return mSwitchFlag; }
};

