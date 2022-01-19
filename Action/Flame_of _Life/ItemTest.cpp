#include "pch.h"

ItemTest::ItemTest(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag, const int _num)
	: ItemBase(_sceneTag, _objectTag)
{
	//GameObjectメンバ変数の初期化
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	// ポジションが動く最大の高さ
	mMaxMove += mPosition.z;
	// ポジションが動く最小（初期ポジ）
	mMinMove = mPosition.z;

	//Component基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Item/Sphere.gpmesh"));

	//当たり判定
	mSelfBoxCollider = new BoxCollider(this, ColliderTag::itemTag, GetOnCollisionFunc());
	AABB box = { Vector3(100.0f,-100.0f,-100.0f),Vector3(-100.0f,100.0f,100.0f) };
	mSelfBoxCollider->SetObjectBox(box);

	// 生成が何番目かによって種類を変える
	switch (_num)
	{
	case(1):
		mItemName = itemNames::cat;
		break;
	case(2):
		mItemName = itemNames::chair;
		break;
	case(3):
		mItemName = itemNames::chara;
		break;
	default:
		break;
	}

	mColor = Vector3(0.5f, 0.5f, 1.5f);
}


void ItemTest::UpdateGameObject(float _deltaTime)
{
	// フラグがさがっていたら
	if (!mCollisionFlag)
	{
		// フラグを見てアイテムの動きを上下させる
		if (mUpFlag)
		{
			mPosition.z += mMove * _deltaTime;
		}
		else
		{
			mPosition.z -= mMove * _deltaTime;
		}
		// 一定数までいったらフラグを変更する
		if (mPosition.z >= mMaxMove)
		{
			mUpFlag = false;
			
		}
		else if(mPosition.z <= mMinMove)
		{
			mUpFlag = true;
			
		}

		SetPosition(mPosition);
	}
	// フラグが上がっていたら
	else if (mCollisionFlag && GetState() != State::Disabling)
	{
		// ステートをdisablにする
		SetState(State::Disabling);

		// アイテムカウントを減らす
		ItemBase::mItemCount--;

		// 取得したアイテムをデータ構造に格納する
		mGetNames.push_back(mItemName);
	}
}


void ItemTest::OnCollision(const GameObject& _hitObject)
{
	// 当たったのでフラグを上げる
	mCollisionFlag = true;

	// 描画をやめる
	mMeshComponent->SetVisible(false);
}
