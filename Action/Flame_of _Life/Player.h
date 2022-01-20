/*
@brief	プリプロセッサ
*/
#pragma once

class Jump;
class LegsCollider;

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
	typedef enum class playerState :unsigned char
	{
		idle,         // 待機
		run,          // 走り

		stateNum           // state_num　必ず最後に書く
							// ステートの個数
	}playerState;


	/*
	@fn		矩形と矩形の押し戻し
	@param	_myAABB	基準にするオブジェクトの矩形当たり判定
	@param	_pairAABB ヒットするオブジェクトの矩形当たり判定
	@param	_pairTag ヒットするオブジェクトのタグ
	*/
	void FixCollision(const AABB& _myAABB, const AABB& _pairAABB, const Tag& _pairTag)override;

	
	//プレイヤーの当たり判定を生成
	BoxCollider* mSelfBoxCollider;
	//スケルタルメッシュ
	SkeletalMeshComponent* mSkelComp;
	
	// 現在の状態
	playerState  mNowState;
	// 1つ前の状態
	playerState  mPrevState;

	// アニメーション
	vector<const class Animation*> mAnimations;
	// 回転目標方向
	Vector3 mAnimVec; 

	// プレイヤーの復帰ポジション
	Vector3 mReturnPos;

	// 落ちた時のポジションと、復帰ポジションの距離
	Vector3 mDifference;

	// カメラポジション
	const Vector3 MCameraPos;

	// カメラのZ軸注視点
	const float MCameraPointZ;

	// プレイヤーのリスポーンするタイミングｚ軸
	const float MRedoingPosZ;

	// リスポーン位置を少し高くする
	float MReturnAddZ;

	// リスポーン時の速度
	const float MRedoingSpeedZ;

	// プレイヤーが動作可能状態か
	bool mOperable;

	// ジャンプ
	Jump* mJump;

	// 足元用の当たり判定
	LegsCollider* mLegs;

	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数(足元判定用)
	@param	当たったGameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;

	/*
	@fn		プレイヤーが落ちた際の処理
	@param	_nowPos	現在のポジション
	@param	_returnPos 復帰位置
	*/
	void mRedoing(Vector3 _nowPos, const Vector3 _returnPos);
	
	
	// アニメーション関係
	
	// アイドル状態
	void mIdleBehavior();
	// ラン状態
	void mRunBehavior();


////デバック用
//	Vector3 testPos;
	bool mDebug;
};

