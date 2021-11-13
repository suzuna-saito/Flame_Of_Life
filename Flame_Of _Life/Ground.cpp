/*
@brief	インクルード
*/
#include "pch.h"


Ground::Ground(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag, const bool _alphaFlag)
	:GameObject(_sceneTag, _objectTag)
	, mAlphaNum(0)
	, mAlphaTiming(0)
	, MTwoTime(250)
	, MThreeTime(500)
	, mCount(1)
	, MAlphaMax(1.2f)
	, MAlphaMin(-0.5f)
	, MAlphaValue(0.01f)
	, mAlphaChange(true)
	, mAlphaGround(_alphaFlag)
	, mFirstFlag(true)
{
	/* 乱数の種を初期化 */
	srand(time(NULL));

	//GameObjectメンバ変数の初期化
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	//SetState(State::Disabling);
	//Component基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Environment/Books/Book_1.gpmesh"));

	//地面の当たり判定
	mSelfBoxCollider = new BoxCollider(this, ColliderTag::groundTag, GetOnCollisionFunc());
	AABB box = { Vector3(13.0f,-20.0f,0.0f),Vector3(-13.0f,16.5f,9.0f) };
	mSelfBoxCollider->SetObjectBox(box);
}

void Ground::UpdateGameObject(float _deltaTime)
{
	mAabb = mSelfBoxCollider->GetWorldBox();

	if (MThreeTime >= mCount)
	{
		mCount++;
	}

	// 透明になる床だったらかつ、タイミングとカウントが一致したら
	if (mAlphaGround && mAlphaTiming <= mCount)
	{
		// 一回目の処理だったら
		if (mFirstFlag)
		{
			// 床の色などを設定する
			mInit();
		}

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
		else if (mAlpha >= MAlphaMax)
		{
			mAlphaChange = true;
		}
	}

	// α値が0.0以下になったら
	if (mAlpha <= 0.0f)
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
		break;
	case green:
		mColor = Color::Green;
		// α値の変わるタイミングをセットする
		mAlphaTiming = MTwoTime;
		break;
	case blue:
		mColor = Color::Blue;
		// α値の変わるタイミングをセットする
		mAlphaTiming = MThreeTime;
		break;
	}
}
