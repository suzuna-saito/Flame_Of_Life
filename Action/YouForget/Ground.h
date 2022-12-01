#pragma once

/*
* 床オブジェクトの処理
*/
class Ground :public GameObject
{
public:
	// 床の種類
	enum class GroundType :unsigned char
	{
		eAlpha,		// 透明になる
		eNotAlpha,	// 透明にならない
	};

	// 床の色
	enum class GroundColor :unsigned char
	{
		eRed,		// 赤
		eGreen,		// 緑
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_pos">ポジション</param>
	/// <param name="_tag">床の種類</param>
	Ground(const Vector3 _pos, const GroundType _tag);
	// デストラクタ
	~Ground() {};

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="_deltaTime">最後のフレームを完了するのに要した時間</param>
	void UpdateGameObject(float _deltaTime)override;

	// 床の種類の数（シーンによって床の色の種類の数が異なる）
	static int mTypeNum;

private:
	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数(足元判定用)
	@param	当たったGameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;

	//ゲームオブジェクトのメッシュポインタ変数
	class MeshComponent* mMeshComponent;

	// 四角の地面の当たり判定を生成
	BoxCollider* mSelfBoxCollider;
	
	// α値の変わっていく速度
	const float MAlphaAddSpeed;
	const float MAlphaSubSpeed;

	// α値の最大値
	float MAlphaMax;
	// α値の最小値
	float MAlphaMin;

	// プレイヤーと接地しているかどうか
	bool mIsPlayer;
	// プレイヤーと接地していたかどうか
	bool mBeforeIsPlayer;

	// 床の種類
	const GroundType MGroundType;
	// 床の色の種類
	GroundColor mAlphaColorTag;

	// 床の色、透明度を設定
	void SetGroundInfo();
};