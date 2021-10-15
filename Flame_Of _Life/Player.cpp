/*
@brief	インクルード
*/
#include "pch.h"


// 定数と静的メンバーの初期化
const float Player::Gravity = 5.0f;

/*
@fn		コンストラクタ
@param	_pos プレイヤーの座標
@param	_size プレイヤーのサイズ
@param	_objectTag プレイヤーのタグ
@param	_sceneTag シーンのタグ
*/
Player::Player(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, _objectTag)
	, mIsGroundFlag(false)
	, mNowJump(false)
	, mMoveSpeed(7.0f)
	, mAccelerator(8.0f)
	, mJump(7.0f)
	, mMaxJump(150.0f)
{
	//GameObjectメンバ変数の初期化
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	//生成したPlayerの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Player/Candle/Candle_1.gpmesh"));

	//プレイヤー自身の当たり判定(ボックス)
	mSelfBoxCollider = new BoxCollider(this, ColliderTag::playerTag, GetOnCollisionFunc());
	AABB box = { Vector3(3.0f,-3.0f,0.0f),Vector3(-3.0f,3.0f,35.0f) };
	mSelfBoxCollider->SetObjectBox(box);

}

/*
@fn		プレイヤーのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void Player::UpdateGameObject(float _deltaTime)
{

	//プレイヤーを見下ろす位置にカメラをセット
	mMainCamera->SetViewMatrixLerpObject(Vector3(0, -700, 150), mPosition);
	//プレイヤーを横から見る位置にカメラをセット
	//mMainCamera->SetViewMatrixLerpObject(Vector3(300, 0, 200), mPosition);

	// 座標をセット
	mPosition += mVelocity;

	// 重力
	if (!mIsGroundFlag)
	{
		mPosition.z -= Gravity;
	}

	mIsGroundFlag = false;

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
	// Wで奥に移動
	if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W))
	{
		mVelocity.y = mMoveSpeed;
	}
	// Sで手前に移動
	else if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S))
	{
		mVelocity.y = -mMoveSpeed;
	}
	// どちらも押されていなければｙ軸の移動を止める
	else
	{
		mVelocity.y = 0.0f;
	}

	// Aで左に移動
	if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A))
	{
		mVelocity.x = mMoveSpeed;
	}
	// Dで右に移動
	else if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D))
	{
		mVelocity.x = -mMoveSpeed;
	}
	// どちらも押されていなければｘ軸の移動を止める
	else
	{
		mVelocity.x = 0.0f;
	}


	///// でバック用 //////
	if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_DOWN))
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
	}
}

/*
@fn		プレイヤーがヒットした時の処理
@param	_hitObject ヒットした対象のゲームオブジェクトのアドレス
*/
void Player::OnCollision(const GameObject& _hitObject)
{
	//ヒットしたオブジェクトのタグを取得
	mTag = _hitObject.GetTag();

	// 床と設置したら
	if (mTag == ground && mPosition.z >= 50.0f )
	{
		mIsGroundFlag = true;

		mVelocity.z = 0.0f;
	}
}