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
	, MCameraPos(Vector3(0, -1300, 1100))
	, mReturnPos(_pos)
	, MCameraPointZ(66.0f)
	, MRedoingPosZ(-400.0f)
	, MReturnAddZ(150.0f)
	, MPosAdjustmentXY(0.1f)
	, MPosAdjustmentZ(50.0f)
	, MSpeedAdjustmentXY(1000.0f)
	, MSpeedAdjustmentZ(4000.0f)
	, mOperable(true)
	, mNowState(playerState::idle)
	, mPrevState(playerState::idle)
{
	//GameObjectメンバ変数の初期化
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	//生成したPlayerの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mSkelComp = new SkeletalMeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mSkelComp->SetMesh(RENDERER->GetMesh("Assets/Player/doll.gpmesh"));

	// スケルトンの読み込み
	mSkelComp->SetSkeleton(RENDERER->GetSkeleton("Assets/Player/doll.gpskel"));

	// アニメーションの読み込み
	mAnimations.resize((int)playerState::stateNum); // 配列を確保（mAnimationsはvector）(STSTE_NUMはenumの中の数)
	mAnimations[(int)playerState::idle] = RENDERER->GetAnimation("Assets/Player/idle.gpanim");
	mAnimations[(int)playerState::run] = RENDERER->GetAnimation("Assets/Player/run.gpanim");

	//アニメーションの再生
	mSkelComp->PlayAnimation(mAnimations[(int)playerState::idle]);

	//プレイヤー自身の当たり判定(ボックス)
	mSelfBoxCollider = new BoxCollider(this, ColliderTag::playerTag, GetOnCollisionFunc());
	AABB box = { Vector3(750.0f,-750.0f,300.0f),Vector3(-750.0f,750.0f,3500.0f) };
	mSelfBoxCollider->SetObjectBox(box);


	//回転処理                        ↓回転する値
	float radian = Math::ToRadians(90.0f);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::UnitZ, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);

	// 足元当たり判定の生成
	mLegs = new LegsCollider(this, _objectTag, _sceneTag);

	// ジャンプを追加
	mJump = new Jump(this);

	// 透明度
	
	mAlpha = 0.1f;

	// でバック用 //
	mDebug = false;

}

/*
@fn		プレイヤーのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void Player::UpdateGameObject(float _deltaTime)
{
	//プレイヤーを見下ろす位置にカメラをセット
	mMainCamera->SetViewMatrixLerpObject(MCameraPos, Vector3(mPosition.x,mPosition.y, MCameraPointZ));
	//プレイヤーを横から見る位置にカメラをセット
	//mMainCamera->SetViewMatrixLerpObject(Vector3(300, 0, 200), mPosition);
	// デバック用
	//mMainCamera->SetViewMatrixLerpObject(Vector3(0, -1000, 200), mPosition + testPos);


	// 現在の状態からそれぞれのふるまいを行う関数にジャンプ
	switch (mNowState)
	{
	case playerState::idle:
		mIdleBehavior();
		break;

	case playerState::run:
		mRunBehavior();
		break;

	default:
		break;
	}

	// ジャンプしてたらジャンプ力を足す
	if (mJump->GetJumpFlag())
	{
 		mVelocity.z += mJump->GetVelocity();
	}

	
	// 重力
 	if (!mLegs->GetIsGround() && !mDebug && mOperable)
	{
		mVelocity.z -= MGravity/* * _deltaTime*/;
	}
	/*else
	{
		mVelocity.z = 0.0f;
	}*/

	// 座標をセット
	mPosition += mVelocity * _deltaTime;

	// 状態が切り替わったらアニメーションを開始
	if (mNowState != mPrevState)
	{
		mSkelComp->PlayAnimation(mAnimations[(int)mNowState], 0.5f);
	}

	if (!mLegs->GetIsGround())
	{
		ComputeWorldTransform();
	}

	//このフレームのステートは1つ前のステートになる
	mPrevState = mNowState;

	
	// プレイヤーが落ちたら
	if (mPosition.z <= MRedoingPosZ && mOperable)
	{
		// 動作が出来なくする
		mOperable = false;

		mVelocity = Vector3::Zero;
	}
	if (!mOperable)
	{
		// 復帰位置まで移動させる
		mRedoing(mPosition, mReturnPos);
	}

	// スイッチ中心に触れていたら
	if (Switch::mSwitchFlag == true && mOperable)
	{
		// 復帰位置を更新
		mReturnPos = mPosition;

		// z軸だけ少し高く
		mReturnPos.z += MReturnAddZ;
	}

	// ポジションをセット
	SetPosition(mPosition);
	mLegs->SetIsGround(false);
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

	if (mOperable)
	{
		mVelocity = Vector3::Zero;

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
		if (_keyState.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::Pressed &&
			mLegs->GetIsGround())
		{
			mJump->SetJumpStart(true);
		}

		// awsdのいずれかが押されていたら
		if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W) || _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S) ||
			_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) || _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D))
		{
			mNowState = playerState::run;
		}
		else
		{
			mNowState = playerState::idle;
			mVelocity = Vector3::Zero;
		}

		// 入力ベクトルの正規化
		inputVec.Normalize();

		mAnimVec = inputVec;

		///// でバック用 //////
		if (_keyState.m_keyboard.GetKeyState(SDL_SCANCODE_B) == ButtonState::Released)
		{
			if (!mDebug)
			{
				mDebug = true;
			}
			else
			{
				mDebug = false;
			}
		}

		if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_UP) && mDebug)
		{
			mVelocity.z = mMoveSpeed;
		}
		else if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_DOWN) && mDebug)
		{
			mVelocity.z = -mMoveSpeed;
		}
		else
		{
			mVelocity.z = 0.0f;
		}
	}
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

	// アイテム、ろうそく、スイッチ中心以外と設置したとき
	if (mTag != Tag::item &&
		mTag != Tag::candle &&
		mTag != Tag::SwitchCenter &&
		mOperable)
	{
		// 押し戻し
		FixCollision(mSelfBoxCollider->GetWorldBox(), _hitObject.GetAabb(), mTag);
	}
}


// 復帰位置まで移動させる
void Player::mRedoing(Vector3 _nowPos, const Vector3 _returnPos)
{
	// 今のポジションと、復帰位置までの差
	Vector3 difference = _returnPos - _nowPos;

	//mPosition = _returnPos;

	difference.Normalize();


	if (mPosition.z < _returnPos.z- MPosAdjustmentZ)
	{
		mVelocity.z = difference.z*MSpeedAdjustmentZ;
	}
	else
	{
		mVelocity.z = 0.0f;

		if (mPosition.x > _returnPos.x + MPosAdjustmentXY || mPosition.x < _returnPos.x - MPosAdjustmentXY)
		{
			mVelocity.x = difference.x * MSpeedAdjustmentXY;
		}
		else
		{
			mVelocity.x = 0.0f;
		}
		if (mPosition.y > _returnPos.y + MPosAdjustmentXY || mPosition.y < _returnPos.y - MPosAdjustmentXY)
		{
			mVelocity.y = difference.y * MSpeedAdjustmentXY;
		}
		else
		{
			mVelocity.y= 0.0f;
		}
	}
	
	if (mVelocity == Vector3::Zero)
	{
		mOperable = true;
	}
	
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
		mSkelComp->PlayAnimation(mAnimations[(int)playerState::idle], 0.5f);
	}
}

// ラン状態の処理
void Player::mRunBehavior()
{
	// 初めてこのステートに入る場合
	if (mNowState != mPrevState)
	{
		mPrevState = mNowState;
		mSkelComp->PlayAnimation(mAnimations[(int)playerState::run], 1.0f);
	}

	// 回転処理
	RotateToNewForward(mAnimVec);
}