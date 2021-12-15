/*
@brief	インクルード
*/
#include "pch.h"


Ground::Ground(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag, const groundTag& _tag)
	:GameObject(_sceneTag, _objectTag)
	, mAlphaNum(0)
	, mAlphaTiming(0)
	, MRedTime(100)
	, MGreenTime(300)
	, MBlueTime(500)
	, mCount(1)
	, MAlphaMax(1.2f)
	, MAlphaMin(-0.5f)
	, MAlphaValue(0.01f)
	, mAlphaChange(true)
	, mFirstFlag(true)
	, mStayPlayer(false)
	, mGroundTag(_tag)
{
	//GameObjectメンバ変数の初期化
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	//Component基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Books/Book_1.gpmesh"));

	//地面の当たり判定
	mSelfBoxCollider = new BoxCollider(this, ColliderTag::groundTag, GetOnCollisionFunc());
	AABB box = { Vector3(13.0f,-20.0f,0.0f),Vector3(-13.0f,16.5f,9.0f) };
	mSelfBoxCollider->SetObjectBox(box);
}

void Ground::UpdateGameObject(float _deltaTime)
{
	mAabb = mSelfBoxCollider->GetWorldBox();

	if (MBlueTime >= mCount)
	{
		mCount++;
	}

	// 一回目の処理
	if (mFirstFlag)
	{
		// タグがRGBalphaだったら
		if (mGroundTag == groundTag::RGBalpha)
		{
			// 床の色などを設定する
			mInit();
		}
		// タグがalphaだったら
		else if (mGroundTag == groundTag::alpha)
		{
			// 色を紫に設定する
			mColor = Vector3(1.0f,0.0f,1.0f);
		}
	}

	// 透明になる床だったらかつ、タイミングとカウントが一致したら
	if ((mGroundTag != groundTag::notAlpha && mGroundTag != groundTag::stayAlpha) && mAlphaTiming <= mCount)
	{
		// mAlphaChangeフラグを見てα値を上げるか下げるか変える
		if (mAlphaChange)
		{
			mAlpha -= MAlphaValue;
		}
		else
		{
			mAlpha += MAlphaValue;
		}

		// 一定数までいったらフラグを変更する
		if (mAlpha <= MAlphaMin)
		{
			mAlphaChange = false;
		}
		else if (mAlpha >= MAlphaMax && mGroundTag != groundTag::stayAlpha)
		{
			mAlphaChange = true;
		}
	}

	/*if (mGroundTag == stayAlpha && mStayPlayer)
	{
		mAlpha += MAlphaValue;
	}*/

	// α値が0.0以下になったら、かつ、RGBの色がついている床だったら
	if (mAlpha <= 0.0f &&( mGroundTag == groundTag::RGBalpha/* || mGroundTag == stayAlpha*/))
	{
		// ステートをdisablにする
		SetState(State::Disabling);
	}
	else
	{
		SetState(State::Active);
	}

	//　ファーストフラグをfalseにする
	mFirstFlag = false;
	// プレイヤーと当たっているかのフラグをfalseに戻す
	mStayPlayer = false;
}

void Ground::OnCollision(const GameObject& _hitObject)
{
	//ヒットしたオブジェクトのタグを取得
	mTag = _hitObject.GetTag();

	// 床と設置したとき
	if (mTag == ground)
	{
		// 接地フラグをtrueにする
		mStayPlayer = true;
	}
}

// 床の色、α値の変わるタイミングを設定する
void Ground::mInit()
{
	// ランダムでmAlphaNamを設定0~2
	mAlphaNum = rand() % 3;

	switch (mAlphaNum)
	{
	case red:
		mColor = Color::Red;
		// α値の変わるタイミングをセットする
		mAlphaTiming = MRedTime;
		break;
	case green:
		mColor = Color::Green;
		// α値の変わるタイミングをセットする
		mAlphaTiming = MGreenTime;
		break;
	case blue:
		mColor = Color::Yellow;
		// α値の変わるタイミングをセットする
		mAlphaTiming = MBlueTime;
		break;
	}
}
