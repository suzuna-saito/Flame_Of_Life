#include "pch.h"

Item::Item(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag, const int _num)
	: ItemBase(_sceneTag, _objectTag)
	, mItemExistsTime(0)
	, MItemExistsOneTime(2100)
	, MItemExistsTwoTime(1700)
	, MItemExistsThreeTime(800)
	, mItemFlashingTime(200)
	, mItemExistsFlag(true)
	, mAlphaDownFlag(true)
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
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Item/Puzzle.gpmesh"));

	// エフェクト
	// アイテムの後ろにあるエフェクト
	mItemEffectManager = new ItemEffectManager(_objectTag, _sceneTag, this);

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

	float radianY = Math::ToRadians(-80.0f*(int)_num);
	rot = this->GetRotation();
	Quaternion incY(Vector3::UnitY, radianY);
	target = Quaternion::Concatenate(rot, incY);
	SetRotation(target);

	float radianX = Math::ToRadians(-40.0f);
	rot = this->GetRotation();
	Quaternion incX(Vector3::UnitX, radianX);
	target = Quaternion::Concatenate(rot, incX);
	SetRotation(target);

	// アイテムのナンバー、アイテムの存在時間
	mItemType(_num);

	// 色
	mColor = Vector3(0.68f, 0.85f, 1.2f);

}


void Item::UpdateGameObject(float _deltaTime)
{
	// プレイヤーと当たっていなかったら
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

		// アイテムの生存時間の計算処理
		mItemExists();

		SetPosition(mPosition);
	}
	// プレイヤーと当たってたら
	else if (mCollisionFlag && GetState() != State::Disabling && mItemExistsFlag)
	{
		// アイテムが存在してないとする
		mItemExistsFlag = false;

		// ステートをdisablにする
		SetState(State::Disabling);

		// アイテムカウントを減らす
		ItemBase::mItemCount--;

		// 取得したアイテムをデータ構造に格納する
		mGetNumber.push_back(mItemNum);
	}

	// 生存フラグがfalseだったら
	if (!mItemExistsFlag)
	{
		// 描画をやめる
		mMeshComponent->SetVisible(false);

		// ステートをdisablにする
		SetState(State::Disabling);
	}
}


void Item::OnCollision(const GameObject& _hitObject)
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

void Item::mItemType(int _num)
{
	// 生成が何番目かによって種類を変える
	switch (_num)
	{
	case((int)ItemNum::one):
		mItemNum = ItemNum::one;
		mItemExistsTime = MItemExistsOneTime;
		break;
	case((int)ItemNum::two):
		mItemNum = ItemNum::two;
		mItemExistsTime = MItemExistsTwoTime;
		break;
	case((int)ItemNum::three):
		mItemNum = ItemNum::three;
		mItemExistsTime = MItemExistsThreeTime;
		break;
	default:
		break;
	}

}

void Item::mItemExists()
{
	if (mAlpha <= 0.0f && mAlphaDownFlag)
	{
		mAlphaDownFlag = false;
	}
	if (mAlpha >= 1.0f && !mAlphaDownFlag)
	{
		mAlphaDownFlag = true;
	}

	// アイテムの生存時間を引いてく
	mItemExistsTime--;

	// 残りの生存時間が200よりも小さくなったら
	if (mItemExistsTime <= mItemFlashingTime)
	{
		// 点滅させる
		if (mAlphaDownFlag)
		{
			mAlpha -= 0.05f;
		}
		else
		{
			mAlpha += 0.05f;
		}
	}

	// 残りの生存時間が0よりも小さくなったら
	if (mItemExistsTime <= 0)
	{
		// 生存フラグをfalseにする
		mItemExistsFlag = false;
	}
}
