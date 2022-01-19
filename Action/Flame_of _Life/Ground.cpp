/*
@brief	インクルード
*/
#include "pch.h"

// 静的メンバ変数の初期化
int Ground::mTypeNum = 0;

Ground::Ground(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag, const groundTag& _tag)
	:GameObject(_sceneTag, _objectTag)
	, mAlphaNum(0)
	, mAlphaTiming(0)
	/*, MRedTime(100)
	, MGreenTime(300)
	, MYellowTime(500)*/
	, mCount(1)
	, MAlphaAddSpeed(0.05f)
	, MAlphaSubSpeed(0.01f)
	, MAlphaMax(1.2f)
	, MAlphaMin(-0.5f)
	, MAlphaValue(0.01f)
	, mAlphaChange(true)
	, mFirstFlag(true)
	, mStayPlayer(false)
	, mGroundTag(_tag)
	, mAlphaColorTag(alphaColor::red)
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

	/* 乱数の種を初期化 */
	srand(time(NULL));

	// 透明度
	if (mGroundTag == groundTag::RGBalpha)
	{
		mAlpha = 0.0f;
	}
}

void Ground::UpdateGameObject(float _deltaTime)
{
	mAabb = mSelfBoxCollider->GetWorldBox();

	/*if (MYellowTime >= mCount)
	{
		mCount++;
	}*/

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

		//　ファーストフラグをfalseにする
		mFirstFlag = false;
	}

	//// スイッチの色と床の色が一緒だったら
	//if (Switch::mSwitchFlag && mAlphaColorTag == Switch::mSwitchColor)
	//{
	//	// 少しずつ透明度をあげる
	//	if (mAlpha <= 1.0f)
	//	{
	//		mAlpha += MAlphaAddSpeed;
	//	}
	//}

	// スイッチの色と床の色が一緒だったら
	if (mGroundTag == groundTag::RGBalpha)
	{
		// スイッチを押していたら
		if (Switch::mSwitchFlag)
		{
			// 少しずつ透明度をあげる
			if (mAlpha <= 1.0f)
			{
				mAlpha += MAlphaAddSpeed;
			}
		}
		else
		{
			// 少しずつ透明度を下げる
			if (mAlpha >= 0.0f)
			{
				mAlpha -= MAlphaSubSpeed;
			}
		}
		/*mAlpha -= Switch::mGetDistance()*0.005;

		if (mAlpha <= 0.0f)
		{
			mAlpha = 0.0f;
		}*/
	}

	
	//// 透明になる床だったらかつ、タイミングとカウントが一致したら
	//if (mGroundTag != groundTag::notAlpha && mAlphaTiming <= mCount)
	//{
	//	// mAlphaChangeフラグを見てα値を上げるか下げるか変える
	//	if (mAlphaChange)
	//	{
	//		mAlpha -= MAlphaValue;
	//	}
	//	else
	//	{
	//		mAlpha += MAlphaValue;
	//	}

	//	// 一定数までいったらフラグを変更する
	//	if (mAlpha <= MAlphaMin)
	//	{
	//		mAlphaChange = false;
	//	}
	//	else if (mAlpha >= MAlphaMax)
	//	{
	//		mAlphaChange = true;
	//	}
	//}
}

void Ground::OnCollision(const GameObject& _hitObject)
{
}

// 床の色、α値の変わるタイミングを設定する
void Ground::mInit()
{
	// ランダムでmAlphaNamを設定
	mAlphaNum = rand() % mTypeNum;

	switch (mAlphaNum)
	{
	case (int)alphaColor::red:
		mColor = Color::Red;
		// 何色の床なのかを設定
		mAlphaColorTag = alphaColor::red;
		break;
	case (int)alphaColor::green:
		mColor = Color::Green;
		// 何色の床なのかを設定
		mAlphaColorTag = alphaColor::green;
		break;
	case (int)alphaColor::yellow:
		mColor = Color::Yellow;
		break;
	}
}
