#pragma once

class SwitchCollider;

// スイッチのオブジェクト
class Switch :public GameObject
{
public:

	// スイッチの色
	enum class switchColor :unsigned char
	{
		red,
		green,
		yellow,
	};

	// コンストラクタ
	Switch(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag, const switchColor& _color);

	/*
	@fn	デストラクタ
	*/
	~Switch() {};

	// 更新
	void UpdateGameObject(float _deltaTime)override;

	// スイッチを押しているかのフラグ
	static bool mSwitchFlag;

	// スイッチの色
	static switchColor mSwitchColor;

private:

	//ゲームオブジェクトのメッシュポインタ変数
	MeshComponent* mMeshComponent;

	// 四角の地面の当たり判定を生成
	BoxCollider* mSelfBoxCollider;

	// それぞれの色のフラグ
	/*bool mRedSwitchFlag;
	bool mGreenSwitchFlag;
	bool mYellowSwitchFlag;*/

	// プレイヤーとスイッチの距離
	static float mDistance;

	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数
	@param	当たったGameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;

	// スイッチ中心の当たり判定
	SwitchCollider* mSwitchCenter;

public: // ゲッター、セッター
};

