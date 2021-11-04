/*
@brief	プリプロセッサ
*/
#pragma once


class Player :public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_pos プレイヤーの座標
	@param	_size プレイヤーのサイズ
	@param	_objectTag プレイヤーのタグ
	@param	_sceneTag シーンのタグ
	*/
	Player(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	/*
	@fn	デストラクタ
	*/
	~Player() {};

	/*
	@fn		プレイヤーのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

	/*
	@fn		入力を引数で受け取る更新関数
	@brief	基本的にここで入力情報を変数に保存しUpdateGameObjectで更新を行う
	@param	_keyState 各入力機器の入力状態
	@brief	キーボード、マウス、コントローラー
	*/
	void GameObjectInput(const InputState& _keyState)override;

private:
	// プレイヤーの行動の状態
	typedef enum PLAYER_STATE
	{
		IDLE,         // 待機
		RUN,          // 走り

		STATE_NUM           // state_num　必ず最後に書く
							// ステートの個数
	};


	/*
@fn		矩形と矩形の押し戻し
@param	_myAABB	基準にするオブジェクトの矩形当たり判定
@param	_pairAABB ヒットするオブジェクトの矩形当たり判定
@param	_pairTag ヒットするオブジェクトのタグ
*/
	void FixCollision(const AABB& _myAABB, const AABB& _pairAABB, const Tag& _pairTag)override;

	//ゲームオブジェクトのメッシュポインタ変数
	MeshComponent* mMeshComponent;
	//プレイヤーの当たり判定を生成
	BoxCollider* mSelfBoxCollider;
	//スケルタルメッシュ
	SkeletalMeshComponent* mSkelComp;
	
	// 現在の状態
	PLAYER_STATE  mNowState;
	// 1つ前の状態
	PLAYER_STATE  mPrevState;

	// カメラポジション
	const Vector3 MCameraPos;
	// アニメーション
	vector<const class Animation*> mAnimations;
	// 回転目標方向
	Vector3 mAnimVec; 

	// 移動スピード
	const float mMoveSpeed;

	// 地面に接地しているどうか
	bool mIsGround;

	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数(足元判定用)
	@param	当たったGameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;

	
	
	// アニメーション関係
	
	// アイドル状態
	void mIdleBehavior();
	// ラン状態
	void mRunBehavior();


////デバック用
//	Vector3 testPos;

public://ゲッターセッター

};

