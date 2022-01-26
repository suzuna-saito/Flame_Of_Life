#include "pch.h"

ItemTest::ItemTest(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag, const int _num)
	: ItemBase(_sceneTag, _objectTag)
	, ItemNumber(_num)
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
	//mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Item/Sphere.gpmesh"));
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Item/Puzzle.gpmesh"));

	//当たり判定
	mSelfBoxCollider = new BoxCollider(this, ColliderTag::itemTag, GetOnCollisionFunc());
	AABB box = { Vector3(3.0f,-3.0f,-3.0f),Vector3(-3.0f,4.0f,3.0f) };
	mSelfBoxCollider->SetObjectBox(box);

	//回転処理                        ↓回転する値
	float radianZ = Math::ToRadians(90.0f);
	Quaternion rot = this->GetRotation();
	Quaternion incZ(Vector3::UnitZ, radianZ);
	Quaternion target = Quaternion::Concatenate(rot, incZ);
	SetRotation(target);

	float radianY = Math::ToRadians(-30.0f*_num);
	rot = this->GetRotation();
	Quaternion incY(Vector3::UnitY, radianY);
	target = Quaternion::Concatenate(rot, incY);
	SetRotation(target);

	// アイテムの種類を決定
	mItemType();
	
	mColor = Vector3(0.5f, 0.5f, 1.0f);
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
	// プレイヤーが操作可能状態の時に当たったら
	if (Player::mOperable)
	{
		// 当たったのでフラグを上げる
		mCollisionFlag = true;

		// 描画をやめる
		mMeshComponent->SetVisible(false);
	}
}

void ItemTest::mItemType()
{
	// 生成が何番目かによって種類を変える
	switch (ItemNumber)
	{
	case(0):
		mItemName = itemNames::cat;
		break;
	case(1):
		mItemName = itemNames::chair;
		break;
	case(2):
		mItemName = itemNames::chara;
		break;
	default:
		break;
	}

}
