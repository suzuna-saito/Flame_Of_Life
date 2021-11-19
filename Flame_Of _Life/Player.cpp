/*
@brief	インクルード
*/
#include "pch.h"


/*
@fn		コンストラクタ
@param	_pos プレイヤーの座標
@param	_size プレイヤーのサイズ
@param	_objectTag プレイヤーのタグ
@param	_sceneTag シーンのタグ
*/
Player::Player(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, _objectTag)
	, mIsGround(false)
	, MCameraPos(Vector3(0, -1000, 450))
	, mNowState(IDLE)
	, mPrevState(IDLE)
{
	//GameObjectメンバ変数の初期化
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	// 生成時のポジションｚを代入
	mPrevPosZ = _pos.z;

	//生成したPlayerの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mSkelComp = new SkeletalMeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mSkelComp->SetMesh(RENDERER->GetMesh("Assets/Player/Doll/doll.gpmesh"));

	// スケルトンの読み込み
	mSkelComp->SetSkeleton(RENDERER->GetSkeleton("Assets/Player/Doll/doll.gpskel"));

	// アニメーションの読み込み
	mAnimations.resize(STATE_NUM); // 配列を確保（mAnimationsはvector）(STSTE_NUMはenumの中の数)
	mAnimations[IDLE] = RENDERER->GetAnimation("Assets/Player/Doll/idle.gpanim");
	mAnimations[RUN] = RENDERER->GetAnimation("Assets/Player/Doll/run.gpanim");

	//アニメーションの再生
	mSkelComp->PlayAnimation(mAnimations[IDLE]);

	//プレイヤー自身の当たり判定(ボックス)
	mSelfBoxCollider = new BoxCollider(this, ColliderTag::playerTag, GetOnCollisionFunc());
	AABB box = { Vector3(750.0f,-750.0f,0.0f),Vector3(-750.0f,750.0f,3500.0f) };
	mSelfBoxCollider->SetObjectBox(box);


	//回転処理                        ↓回転する値
	float radian = Math::ToRadians(90.0f);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::UnitZ, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);


	// ジャンプを追加
	mJump = new Jump(this);
}

/*
@fn		プレイヤーのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void Player::UpdateGameObject(float _deltaTime)
{

	//プレイヤーを見下ろす位置にカメラをセット
	mMainCamera->SetViewMatrixLerpObject(MCameraPos, mPosition);
	//プレイヤーを横から見る位置にカメラをセット
	//mMainCamera->SetViewMatrixLerpObject(Vector3(300, 0, 200), mPosition);
	// デバック用
	//mMainCamera->SetViewMatrixLerpObject(Vector3(0, -1000, 200), mPosition + testPos);


	// 現在の状態からそれぞれのふるまいを行う関数にジャンプ
	switch (mNowState)
	{
	case IDLE:
		mIdleBehavior();
		break;

	case RUN:
		mRunBehavior();
		break;

	default:
		break;
	}


	// 座標をセット
	mPosition += mVelocity;

	// ジャンプしてたらジャンプ力を足す
	if (mJump->GetJumpFlag())
	{
		mPosition += mJump->GetAddPos();
	}


	// 重力
	if (!mIsGround)
	{
		mPosition.z -= MGravity;
	}

	mIsGround = false;
	

	// 状態が切り替わったらアニメーションを開始
	if (mNowState != mPrevState)
	{
		mSkelComp->PlayAnimation(mAnimations[mNowState], 0.5f);
	}

	if (!mIsGround)
	{
		ComputeWorldTransform();
	}

	//このフレームのステートは1つ前のステートになる
	mPrevState = mNowState;


	// ポジションをセット
	SetPosition(mPosition);
}

/*
@fn		入力を引数で受け取る更新関数
@brief	基本的にここで入力情報を変数に保存しUpdateGameObjectで更新を行う
@param	_keyState 各入力機器の入力状態
@brief	キーボード、マウス、コントローラー
*/
void Player::GameObjectInput(const InputState& _keyState)
{
	// 向いてほしい向きのベクトル
	Vector3 inputVec = Vector3::Zero;

	// Wで奥に移動
	if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W))
	{
		inputVec.y = 1.0f;
		mVelocity.y = mMoveSpeed;
	}
	// Sで手前に移動
	else if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S))
	{
		inputVec.y = -1.0f;
		mVelocity.y = -mMoveSpeed;
	}
	else
	{
		mVelocity.y = 0.0f;
	}
	// Aで左に移動
	if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A))
	{
		inputVec.x = 1.0f;
		mVelocity.x = mMoveSpeed;
	}
	// Dで右に移動
	else if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D))
	{
		inputVec.x = -1.0f;
		mVelocity.x = -mMoveSpeed;
	}
	else
	{
		mVelocity.x = 0.0f;
	}

	// スペースでジャンプ
	if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_SPACE) == 1 && mIsGround)
	{
		mJump->SetJumpFlag(true);
	}

	// awsdのいずれかが押されていたら
	if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W) || _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S) ||
		_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) || _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D))
	{
		mNowState = RUN;
	}
	else
	{
		mNowState = IDLE;
		mVelocity = Vector3::Zero;
	}

	// 入力ベクトルの正規化
	inputVec.Normalize();

	mAnimVec = inputVec;

	///// でバック用 //////
	/*if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_DOWN))
	{
		mVelocity.z = -mMoveSpeed;
	}
	else if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_UP))
	{
		mVelocity.z = mMoveSpeed;
	}
	else
	{
		mVelocity.z = 0.0f;
	}*/
}

/*
@fn		矩形と矩形の押し戻し
@param	_myAABB	基準にするオブジェクトの矩形当たり判定
@param	_pairAABB ヒットするオブジェクトの矩形当たり判定
@param	_pairTag ヒットするオブジェクトのタグ
*/
void Player::FixCollision(const AABB& _myAABB, const AABB& _pairAABB, const Tag& _pairTag)
{
	Vector3 ment = Vector3::Zero;
	CalcCollisionFixVec(_myAABB, _pairAABB, ment);

	SetPosition(mPosition + ment);
}

/*
@fn		プレイヤーがヒットした時の処理
@param	_hitObject ヒットした対象のゲームオブジェクトのアドレス
*/
void Player::OnCollision(const GameObject& _hitObject)
{
	//ヒットしたオブジェクトのタグを取得
	mTag = _hitObject.GetTag();

	// 床と設置したとき、PrevPosよりも現在のポジションの位置が上だったら
	if (mTag == ground)
	{
		// 接地フラグをtrueにする
		mIsGround = true;

		// PrevPosに現在のポジションを代入
		mPrevPosZ = mPosition.z;

		// 押し戻し
		FixCollision(mSelfBoxCollider->GetWorldBox(), _hitObject.GetAabb(), mTag);
	}

	//// 押し戻し
	//FixCollision(mSelfBoxCollider->GetWorldBox(), _hitObject.GetAabb(), mTag);
}


/*
アニメーション
*/

// アイドル状態の処理
void Player::mIdleBehavior()
{
	// 初めてこのステートに入る場合
	if (mNowState != mPrevState)
	{
		// 待機アニメーション再生開始
		mPrevState = mNowState;
		mSkelComp->PlayAnimation(mAnimations[IDLE], 0.5f);
	}
}

// ラン状態の処理
void Player::mRunBehavior()
{
	// 初めてこのステートに入る場合
	if (mNowState != mPrevState)
	{
		mPrevState = mNowState;
		mSkelComp->PlayAnimation(mAnimations[RUN], 1.0f);
	}

	// 回転処理
	RotateToNewForward(mAnimVec);
}