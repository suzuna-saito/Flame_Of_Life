#include "pch.h"

// 静的メンバ変数の初期化
int Ground::mTypeNum = 0;

Ground::Ground(const Vector3 _pos, const GroundType _tag)
	: GameObject(ObjTag::eGround)
	, MAlphaAddSpeed(4.5f)
	, MAlphaSubSpeed(0.8f)
	, MAlphaMax(1.2f)
	, MGroundType(_tag)
	, mAlphaColorTag(GroundColor::eRed)
	, mIsPlayer(false)
	, mBeforeIsPlayer(false)
{
	// MeshComponentを生成することで自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);
	// Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Books/Book_1.gpmesh"));

	// 当たり判定
	mSelfBoxCollider = new BoxCollider(this, mTag, GetOnCollisionFunc());
	AABB box = { Vector3(-14.5f,-21.5f,0.0f),Vector3(14.5f,20.0f,9.0f) };
	mSelfBoxCollider->SetObjectBox(box);

	// GameObjectメンバ変数の初期化
	SetScale(Vector3(10.0f, 10.0f, 10.0f));		// スケール
	SetPosition(_pos);							// ポジション

	// 床の色、透明度を設定
	SetGroundInfo();
}

void Ground::SetGroundInfo()
{
	// 透明にならない床だったら
	if (MGroundType == GroundType::eNotAlpha)
	{
		mColor = Color::White;				// 色を白に設定
		return;
	}

	// ランダムで整数を取得
	int randNum = rand() % mTypeNum;

	// 値が赤と一致したら
	if (randNum == (int)GroundColor::eRed)
	{
		mColor = Vector3(1.0f, 0.6f, 0.6f); // 色をうすい赤に設定
		mAlphaColorTag = GroundColor::eRed;	// 床の色の種類を赤に設定
	}
	else
	{
		mColor = Color::LightGreen;			// 色を黄緑に設定
		mAlphaColorTag = GroundColor::eGreen;
	}

	// 透明度を0.0fに設定
	mAlpha = 0.0f;
}

void Ground::UpdateGameObject(float _deltaTime)
{
	// AABBを毎ループ更新
	mAabb = mSelfBoxCollider->GetWorldBox();

	// 床の透明度が0より小さかったらまたは、スイッチが押されたら
	if (mAlpha <= 0.0f || Switch::mFollowSwitchFlag)
	{
		// プレイヤーが乗っていなかった判定にする
		mBeforeIsPlayer = false;
	}

	// スイッチを押していたらかつ、今踏んでるスイッチの色と床の色が一緒だったら
	if (Switch::mFollowSwitchFlag && MGroundType == GroundType::eAlpha &&
		mAlphaColorTag == SwitchCollider::mLinkageColor)
	{
		// 少しずつ透明度をあげる
		if (mAlpha <= MAlphaMax)
		{
			mAlpha += MAlphaAddSpeed* _deltaTime;
		}
	}
	// プレイヤーが乗っている床だったら
	else if (mIsPlayer)
	{
		// 少しずつ透明度をあげる
		if (mAlpha <= MAlphaMax-0.7f)
		{
			mAlpha += (MAlphaAddSpeed * 1.5f)*_deltaTime;
		}
	}

	// スイッチを押していないかつ、プレイヤーが乗っていなかったら
	if(!Switch::mFollowSwitchFlag && MGroundType != GroundType::eNotAlpha && !mIsPlayer && !mBeforeIsPlayer ||
		Switch::mFollowSwitchFlag && MGroundType != GroundType::eNotAlpha && mAlphaColorTag != SwitchCollider::mLinkageColor)
	{
		// 少しずつ透明度を下げる
		if (mAlpha >= 0.0f)
		{
			mAlpha -= MAlphaSubSpeed * _deltaTime;
		}
	}
	else if (MGroundType != GroundType::eNotAlpha && !mIsPlayer && mBeforeIsPlayer)
	{
		// 少しずつ透明度を下げる
		if (mAlpha >= 0.0f)
		{
			mAlpha -= (MAlphaSubSpeed*1.9f) * _deltaTime;
		}
	}

	// プレイヤーが落ちたら
	if (!Player::mOperable && mAlpha <= 1.0f)
	{
		// 床が見えるようにする
		mAlpha += MAlphaAddSpeed * _deltaTime;
	}


	// プレイヤーが前乗っていなくてかつ、今乗っていたら
	if (mBeforeIsPlayer != mIsPlayer && !mBeforeIsPlayer)
	{
		mBeforeIsPlayer = mIsPlayer;
	}
	

	mIsPlayer = false;
}

void Ground::OnCollision(const GameObject& _hitObject)
{
	//ヒットしたオブジェクトのタグを取得
	ObjTag hitObjectTag = _hitObject.GetTag();

	if (hitObjectTag == ObjTag::ePlayerLegs)
	{
		mIsPlayer = true;
	}
}
