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

	//ゲームオブジェクトのメッシュポインタ変数
	MeshComponent* mMeshComponent;
	//プレイヤーの球当たり判定を生成
	//SphereCollider*		mSelfSphereCollider;
	BoxCollider* mSelfBoxCollider;

	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数(足元判定用)
	@param	当たったGameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;


	// 重力
	static const float Gravity;

	// 移動スピード
	const float mMoveSpeed;

	// 地面に接地しているどうか
	bool mIsGroundFlag;

	// 最初のジャンプ力
	const float mAccelerator;
	// ジャンプ力
	const float mJump;
	// 最大ジャンプ力
	const float mMaxJump;
	// ジャンプ中かどうか
	bool mNowJump;

public://ゲッターセッター

};

