/*
@brief	プリプロセッサ
*/
#pragma once

class Ground :public GameObject
{
public:

	// 床の種類
	enum groundTag
	{
		// 透明になる（ｒｇｂ）
		RGBalpha,
		// 透明になる（固定の色）
		alpha,
		// 透明にならない
		notAlpha,
		// 長時間いたら消える床
		stayAlpha
	};

	/*
	@fn		コンストラクタ
	@param	_pos ポジション
	@param	_size サイズ
	@param	_objectTag オブジェクトのタグ
	@param	_sceneTag シーンタグ
	@param	_tag 床の種類
	*/
	Ground(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag,const groundTag& _tag);

	// デストラクタ
	~Ground() {};

	/*
	@fn		床のアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数(足元判定用)
	@param	当たったGameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;

	//ゲームオブジェクトのメッシュポインタ変数
	MeshComponent* mMeshComponent;

	// 四角の地面の当たり判定を生成
	BoxCollider* mSelfBoxCollider;

	// α値の変わるタイミング種類&床の色
	enum alphaColor
	{
		red,
		green,
		blue
	};

	// α値の変わるタイミング種類
	int mAlphaNum;
	// α値の変わるタイミング
	int mAlphaTiming;
	// α値の変わるカウント
	int mCount;
	// 赤の床の色が変わるタイミング
	const int MRedTime;
	// 緑の床の色が変わるタイミング
	const int MGreenTime;
	// 青の床の色が変わるタイミング
	const int MBlueTime;

	// α値の最大値
	float MAlphaMax;
	// α値の最小値
	float MAlphaMin;
	// α値の変わる速度
	float MAlphaValue;

	// 床の透明度が上がるか下がるか true: 上がる false: 下がる
	bool mAlphaChange;
	// 処理を通るのは初めてか true: 初めて
	bool mFirstFlag;
	// プレイヤーと当たっているかどうか
	bool mStayPlayer;

	// 床の種類
	groundTag mGroundTag;

	/*
	@fn		床の色、α値の変わるタイミングを設定する
	*/
	void mInit();

};

