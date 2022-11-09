#pragma once

/*
* マークがついている床の処理
*/
class Switch :public GameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_pos">ポジション</param>
	/// <param name="_color">生成したい床の色の種類<</param>
	Switch(const Vector3 _pos, const Ground::GroundColor _color);
	// デストラクタ
	~Switch() {};

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="_deltaTime">最後のフレームを完了するのに要した時間</param>
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