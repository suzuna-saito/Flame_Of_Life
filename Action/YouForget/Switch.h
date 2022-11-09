#pragma once

// スイッチのオブジェクト
class Switch :public GameObject
{
public:
	// スイッチの色
	enum class switchColor :unsigned char
	{
		red,	// 赤
		green,	// 緑
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_pos">ポジション</param>
	/// <param name="_color">生成したい色の種類<</param>
	Switch(const Vector3 _pos, const switchColor& _color);
	// デストラクタ
	~Switch() {};

	// 更新
	void UpdateGameObject(float _deltaTime)override;

	// スイッチを押しているかのフラグ
	static bool mFollowSwitchFlag;

private:

	//ゲームオブジェクトのメッシュポインタ変数
	MeshComponent* mMeshComponent;

	// 四角の地面の当たり判定を生成
	BoxCollider* mSelfBoxCollider;

	// スイッチ中心の当たり判定
	class SwitchCollider* mSwitchCenter;
};