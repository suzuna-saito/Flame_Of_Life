/*
@brief	プリプロセッサ
*/
#pragma once

class Ground :public GameObject
{
public:
	/*
	@fn		コンストラクタ
	@param	_pos ポジション
	@param	_size サイズ
	@param	_objectTag オブジェクトのタグ
	@param	_sceneTag シーンタグ
	@param	_alphaFlag 透明にする床かどうか true: 透明にする false: 透明にしない
	*/
	Ground(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag, const bool _alphaFlag);

	// デストラクタ
	~Ground() {};

	/*
	@fn		床のアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
	//ゲームオブジェクトのメッシュポインタ変数
	MeshComponent* mMeshComponent;

	// 四角の地面の当たり判定を生成
	BoxCollider* mSelfBoxCollider;

	// α値の変わるタイミング種類&床の色
	enum Alpha
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

	const int MTwoTime;
	const int MThreeTime;

	// α値の最大値
	float MAlphaMax;
	// α値の最小値
	float MAlphaMin;
	// α値の変わる速度
	float MAlphaValue;

	// 床の透明度が上がるか下がるか true: 上がる false: 下がる
	bool mAlphaChange;
	// 透明になる床かどうか
	bool mAlphaGround;
	// 処理を通るのは初めてか true: 初めて
	bool mFirstFlag;

	/*
	@fn		床の色、α値の変わるタイミングを設定する
	*/
	void mInit();
};

