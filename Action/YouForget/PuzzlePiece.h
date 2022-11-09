/*
* パズルピース（収集物）の処理
*/
class PuzzlePiece :public GameObject
{
public:
	// パズルピースのナンバー
	enum class PieceNum : unsigned char
	{
		eOne,
		eTwo,
		eThree,
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_pos">ポジション</param>
	/// <param name="_num">何個目のピースか</param>
	PuzzlePiece(const Vector3 _pos, const int _num);
	// デストラクタ
	~PuzzlePiece() {};

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="_deltaTime">最後のフレームを完了するのに要した時間</param>
	void UpdateGameObject(float _deltaTime)override;

	// 収集したパズルピースを格納するためのデータ構造
	static vector<PieceNum> mGetNumber;

private:
	/// <summary>
	/// 当たり判定が行われHitした際に呼ばれる関数
	/// </summary>
	/// <param name="_hitObject">Hitした対象のゲームオブジェクトのアドレス</param>
	void OnCollision(const GameObject& _hitObject)override;

	/// <summary>
	/// パズルピースのナンバー、生存時間を設定
	/// </summary>
	/// <param name="_num">ピースの生成番号</param>
	void SetPieceInfo(int _num);
	// パズルピースの生存時間の計算
	void PieceExists();

	class MeshComponent* mMeshComponent;	// ゲームオブジェクトのメッシュポインタ変数
	class BoxCollider* mSelfBoxCollider;	// 四角の当たり判定

	PieceNum mPieceNum;		// ピースの種類

	// ピースの上下移動pos値
	const float MMaxPos;	// 最大値
	const float MMinPos;	// 最小値

	float mPosMove;			// ポジションの移動値
	float mAlphaMove;		// α値の変更値

	int mPieceExistsTime;	// ピースのそれぞれの生存時間
	int mPieceFlashingTime;	// ピースが点滅し始める時間

	bool mPieceExistsFlag;	// ピースがまだ存在しているかのフラグ true _存在する false _存在しない
	bool mCollisionFlag;	// プレイヤーと当たったかどうかの判定
};